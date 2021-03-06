#include "amp.h"

#include <stddef.h>

#include "audio/audio.h"
#include "bt.h"
#include "control.h"
#include "debug.h"
#include "gui/canvas.h"
#include "i2c.h"
#include "i2cexp.h"
#include "input.h"
#include "mpc.h"
#include "menu.h"
#include "pins.h"
#include "rc.h"
#include "rtc.h"
#include "settings.h"
#include "spectrum.h"
#include "swtimers.h"
#include "timers.h"
#include "tr/labels.h"
#include "tuner/rds/parser.h"
#include "tuner/stations.h"
#include "tuner/tuner.h"
#include "utils.h"

#ifdef _ENABLE_USB
#include "usb/hidkeys.h"
#include "usb/usbhid.h"
#endif

static void actionGetButtons(void);
static void actionGetEncoder(void);
static void actionGetRemote(void);
static void actionGetTimers(void);

static void actionRemapBtnShort(void);
static void actionRemapBtnLong(void);
static void actionRemapRemote(void);
static void actionRemapCommon(void);
static void actionRemapNavigate(void);
static void actionRemapEncoder(void);

static void ampActionGet(void);
static void ampActionRemap(void);
static void ampActionHandle(void);

static void ampScreenShow(void);

static void ampSendMediaKey(MediaKey key);

static Amp amp = {
    .status = AMP_STATUS_STBY,
    .screen = SCREEN_STANDBY,
    .defScreen = SCREEN_SPECTRUM,
    .inputStatus = 0x00,
    .volume = 0,
};

static Action action = {
    .type = ACTION_NONE,
    .value = FLAG_ENTER,
};

static Screen screen = {
    .type = SCREEN_STANDBY,
    .timeout = SW_TIM_OFF,
};

static void actionSet(ActionType type, int16_t value)
{
    action.type = type;
    action.value = value;
}

static void screenSet(ScreenType type, int16_t timeout)
{
    screen.type = type;
    screen.timeout = timeout;
}

static void rdsParserCb(void)
{
    swTimSet(SW_TIM_RDS_HOLD, 1000);
}

static bool screenCheckClear(void)
{
    bool clear = false;

    if (amp.clearScreen) {
        clear = true;
        amp.clearScreen = false;
    } else if (amp.screen != amp.prevScreen) {
        clear = true;
        switch (amp.screen) {
        case SCREEN_STANDBY:
        case SCREEN_TIME:
            if (amp.prevScreen == SCREEN_STANDBY || amp.prevScreen == SCREEN_TIME) {
                clear = false;
            }
            break;
        case SCREEN_MENU:
            menuGet()->selected = 0;
            break;
        default:
            break;
        }
    }

    if (amp.screen != amp.prevScreen || clear) {
        // Handle standby/work brightness
        ampSetBrightness((int8_t)settingsGet(amp.screen == SCREEN_STANDBY ?
                                             PARAM_DISPLAY_BR_STBY : PARAM_DISPLAY_BR_WORK));
    }


    // Save current screen and screen parameter
    amp.prevScreen = amp.screen;

    return clear;
}

static void ampScreenPwm(void)
{
    static int8_t br;

    if (++br >= LCD_BR_MAX) {
        br = 0;
    }

    if (br == amp.brightness) {
        glcdSetBacklight(false);
    } else if (br == 0) {
        glcdSetBacklight(true);
    }
}
static void actionDispExpired(ScreenType scrMode)
{
    AudioProc *aProc = audioGet();

    ScreenType scrDef = amp.defScreen;

    int32_t timer;

    timer = swTimGet(SW_TIM_SCREEN_SAVER);
    if (timer == 0) {
        scrDef = SCREEN_SAVER;
    }

    timer = swTimGet(SW_TIM_STBY_TIMER);
    if (timer > 0 && timer < 60 * 1000 + 999) {
        scrDef = SCREEN_STBY_TIMER;
    }
    timer = swTimGet(SW_TIM_SILENCE_TIMER);
    if (timer > 0 && timer < 30 * 1000 + 999) {
        scrDef = SCREEN_SILENCE_TIMER;
    }

    if (aProc->par.mute) {
        scrDef = SCREEN_AUDIO_INPUT;
    }

    amp.iconHint = ICON_EMPTY;

    rtcSetMode(RTC_NOEDIT);
    aProc->tune = (scrDef == SCREEN_AUDIO_INPUT ? AUDIO_TUNE_GAIN : AUDIO_TUNE_VOLUME);

    switch (scrMode) {
    case SCREEN_STANDBY:
    case SCREEN_MENU:
        screenSet(SCREEN_STANDBY, 1000); // TODO: Return to parent screen caused menu
        break;
    default:
        screenSet(scrDef, 1000);
        break;
    }
}

static void actionResetSilenceTimer(void)
{
    int16_t silenceTimer = settingsGet(PARAM_SYSTEM_SIL_TIM);

    if (silenceTimer) {
        swTimSet(SW_TIM_SILENCE_TIMER, 1000 * 60 * silenceTimer + 999);
    }

    swTimSet(SW_TIM_SCREEN_SAVER, 1000 * 20);
}

static void inputDisable(void)
{
    AudioProc *aProc = audioGet();
    InputType inType = amp.inType[aProc->par.input];

    switch (inType) {
    case IN_TUNER:
        swTimSet(SW_TIM_RDS_HOLD, SW_TIM_OFF);
        tunerSetPower(false);
        break;
    case IN_KARADIO:
    case IN_BLUETOOTH:
        ampSendMediaKey(MEDIAKEY_STOP);
        break;
    default:
        break;
    }

    // TODO: Power off current input device
}

static void inputEnable(void)
{
    Tuner *tuner = tunerGet();
    AudioProc *aProc = audioGet();
    InputType inType = amp.inType[aProc->par.input];

    switch (inType) {
    case IN_TUNER:
        swTimSet(SW_TIM_RDS_HOLD, SW_TIM_OFF);
        tunerSetPower(true);
        tunerSetVolume(tuner->par.volume);
        tunerSetMute(false);
        tunerSetFreq(tuner->status.freq);
        break;
    case IN_MPD:
        mpcSyncRequest();
    case IN_KARADIO:
    case IN_BLUETOOTH:
        ampSendMediaKey(MEDIAKEY_PLAY);
        break;
    default:
        break;
    }
}

static void inputSetPower(bool value)
{
    AudioProc *aProc = audioGet();
    int8_t input = aProc->par.input;

    if (value) {
        amp.inputStatus = (uint8_t)(1 << input);
    } else {
        amp.inputStatus = 0x00;
    }

    I2cAddrIdx i2cAddrIdx = (I2cAddrIdx)settingsGet(PARAM_I2C_EXT_IN_STAT);

    if (i2cAddrIdx != I2C_ADDR_DISABLED) {
        if (!i2cIsEnabled(I2C_AMP)) {
            i2cInit(I2C_AMP, 100000, 0x00);
            i2cexpSend(i2cAddrIdx, amp.inputStatus);
            i2cDeInit(I2C_AMP);
        } else {
            i2cexpSend(i2cAddrIdx, amp.inputStatus);
        }
    }
}

void ampPinMute(bool value)
{
    bool muteLow = (bool)settingsGet(PARAM_SYSTEM_MUTE_LOW);

    if (muteLow) {
        if (value) {
            SET(MUTE);
        } else {
            CLR(MUTE);
        }
    } else {
        if (value) {
            CLR(MUTE);
        } else {
            SET(MUTE);
        }
    }
}

void ampPinStby(bool value)
{
    bool stbyLow = (bool)settingsGet(PARAM_SYSTEM_STBY_LOW);

    if (stbyLow) {
        if (value) {
            SET(STBY);
        } else {
            CLR(STBY);
        }
    } else {
        if (value) {
            CLR(STBY);
        } else {
            SET(STBY);
        }
    }
}

static void ampMute(bool value)
{
    AudioProc *aProc = audioGet();
    AudioTuneItem *volItem = &aProc->par.tune[AUDIO_TUNE_VOLUME];

    if (value) {
        swTimSet(SW_TIM_SOFT_VOLUME, SW_TIM_OFF);
    } else {
        audioSetTune(AUDIO_TUNE_VOLUME, volItem->grid->min);
        swTimSet(SW_TIM_SOFT_VOLUME, SW_TIM_ON);
    }

    ampPinMute(value);
    audioSetMute(value);
}

static void ampReadSettings(void)
{
    audioReadSettings(AUDIO_IC_TDA7439);
    tunerReadSettings(TUNER_IC_RDA5807);
}

static void ampVolumeInit(void)
{
    AudioProc *aProc = audioGet();
    AudioTuneItem *volItem = &aProc->par.tune[AUDIO_TUNE_VOLUME];

    amp.volume = volItem->value;
    volItem->value = volItem->grid->min;
}

static void ampExitStby(void)
{
    ampReadSettings();

    ampPinStby(false);      // Power on amplifier

    inputSetPower(true);    // Power on input device

    amp.status = AMP_STATUS_POWERED;

    swTimSet(SW_TIM_AMP_INIT, 600);
    swTimSet(SW_TIM_SP_CONVERT, SW_TIM_ON);
}

static void ampEnterStby(void)
{
    swTimSet(SW_TIM_STBY_TIMER, SW_TIM_OFF);
    swTimSet(SW_TIM_SCREEN_SAVER, SW_TIM_OFF);
    swTimSet(SW_TIM_SILENCE_TIMER, SW_TIM_OFF);
    swTimSet(SW_TIM_INPUT_POLL, SW_TIM_OFF);
    swTimSet(SW_TIM_SP_CONVERT, SW_TIM_OFF);

    settingsSet(PARAM_DISPLAY_DEF, amp.defScreen);
    settingsStore(PARAM_DISPLAY_DEF, amp.defScreen);

    ampMute(true);

    // Restore volume value before saving
    AudioProc *aProc = audioGet();
    AudioTuneItem *volItem = &aProc->par.tune[AUDIO_TUNE_VOLUME];
    volItem->value = amp.volume;

    audioSetPower(false);

    inputDisable();

    inputSetPower(false);   // Power off input device

    amp.status = AMP_STATUS_STBY;
    controlReportAmpStatus();
    swTimSet(SW_TIM_AMP_INIT, 1000);
}

void ampInitHw(void)
{
    swTimSet(SW_TIM_AMP_INIT, SW_TIM_OFF);

    switch (amp.status) {
    case AMP_STATUS_POWERED:
        pinsHwResetI2c();
        i2cInit(I2C_AMP, 100000, 0x00);

        audioInit();
        ampVolumeInit();

        audioSetPower(true);
        ampMute(true);

        swTimSet(SW_TIM_RDS_HOLD, SW_TIM_OFF);
        tunerInit();

        btInit();

        amp.status = AMP_STATUS_HW_READY;
        controlReportAll();

        swTimSet(SW_TIM_AMP_INIT, 500);
        break;
    case AMP_STATUS_HW_READY:
        inputEnable();

        ampMute(false);

        amp.status = AMP_STATUS_ACTIVE;

        swTimSet(SW_TIM_INPUT_POLL, 100);
        break;
    case AMP_STATUS_STBY:
        swTimSet(SW_TIM_AMP_INIT, SW_TIM_OFF);
        ampPinStby(true);
        break;
    }
}

static void ampSetInput(int8_t value)
{
    swTimSet(SW_TIM_INPUT_POLL, SW_TIM_OFF);

    ampMute(true);

    inputDisable();
    inputSetPower(false);
    audioSetInput(value);
    inputSetPower(true);

    amp.status = AMP_STATUS_HW_READY;
    swTimSet(SW_TIM_AMP_INIT, 400);
}


static void actionNavigateMenu(RcCmd cmd)
{
    Menu *menu = menuGet();

    switch (cmd) {
    case RC_CMD_NAV_OK:
    case RC_CMD_NAV_RIGHT:
        actionSet(ACTION_MENU_SELECT, (int16_t)(menuGetFirstChild()));
        break;
    case RC_CMD_NAV_BACK:
    case RC_CMD_NAV_LEFT:
        if (menu->selected) {
            menu->selected = false;
        } else if (menuIsTop()) {
            // TODO: Return to original screen called menu
            actionSet(ACTION_STANDBY, FLAG_ENTER);
        } else {
            actionSet(ACTION_MENU_SELECT, (int16_t)menu->parent);
        }
        break;
    case RC_CMD_NAV_UP:
    case RC_CMD_CHAN_PREV:
        actionSet(ACTION_MENU_CHANGE, -1);
        break;
    case RC_CMD_NAV_DOWN:
    case RC_CMD_CHAN_NEXT:
        actionSet(ACTION_MENU_CHANGE, +1);
        break;
    }
}

static void actionNavigateTextEdit(RcCmd cmd)
{
    switch (cmd) {
    case RC_CMD_NAV_OK:
        action.type = ACTION_TEXTEDIT_APPLY;
        break;
    case RC_CMD_NAV_BACK:
        action.type = ACTION_TEXTEDIT_CANCEL;
        break;
    case RC_CMD_NAV_RIGHT:
    case RC_CMD_CHAN_NEXT:
        action.type = ACTION_TEXTEDIT_ADD_CHAR;
        break;
    case RC_CMD_NAV_LEFT:
    case RC_CMD_CHAN_PREV:
        action.type = ACTION_TEXTEDIT_DEL_CHAR;
        break;
    case RC_CMD_NAV_UP:
        actionSet(ACTION_ENCODER, -1);
        break;
    case RC_CMD_NAV_DOWN:
        actionSet(ACTION_ENCODER, +1);
        break;
    }
}

static void actionNavigateCommon(RcCmd cmd)
{
    switch (cmd) {
    case RC_CMD_NAV_OK:
        action.type = ACTION_OPEN_MENU;
        break;
    case RC_CMD_NAV_BACK:
        actionSet(ACTION_MEDIA, MEDIAKEY_PLAY);
        break;
    case RC_CMD_NAV_RIGHT:
        actionSet(ACTION_MEDIA, MEDIAKEY_FFWD);
        break;
    case RC_CMD_NAV_LEFT:
        actionSet(ACTION_MEDIA, MEDIAKEY_REWIND);
        break;
    case RC_CMD_NAV_UP:
    case RC_CMD_CHAN_NEXT:
        actionSet(ACTION_MEDIA, MEDIAKEY_NEXT);
        break;
    case RC_CMD_NAV_DOWN:
    case RC_CMD_CHAN_PREV:
        actionSet(ACTION_MEDIA, MEDIAKEY_PREV);
        break;
    }
}

static void actionNextAudioParam(AudioProc *aProc)
{
    do {
        aProc->tune++;
        if (aProc->tune >= AUDIO_TUNE_END)
            aProc->tune = AUDIO_TUNE_VOLUME;
    } while (aProc->par.tune[aProc->tune].grid == NULL && aProc->tune != AUDIO_TUNE_VOLUME);
}

static int8_t actionGetNextAudioInput(int8_t diff)
{
    AudioProc *aProc = audioGet();

    int8_t input = aProc->par.input;
    int8_t inCnt = aProc->par.inCnt;

    int8_t ret = input;

    do {
        ret += diff;
        if (ret < 0) {
            ret = inCnt - 1;
        } else if (ret >= inCnt) {
            ret = 0;
        }
    } while ((amp.inType[ret] == IN_DISABLED) && (ret != input));

    return ret;
}

static void actionSetInput(int8_t value)
{
    ampSetInput(value);
    controlReportAudioInput();
    controlReportAudioTune(AUDIO_TUNE_GAIN);
}

static void actionPostSetInput(void)
{
    amp.clearScreen = true;
    amp.iconHint = ICON_EMPTY;
    screenSet(SCREEN_AUDIO_INPUT, 5000);
}

static void actionGetButtons(void)
{
    CmdBtn cmdBtn = inputGetBtnCmd();

    if (cmdBtn.btn) {
        if (cmdBtn.flags & BTN_FLAG_LONG_PRESS) {
            actionSet(ACTION_BTN_LONG, (int16_t)cmdBtn.btn);
        } else {
            actionSet(ACTION_BTN_SHORT, (int16_t)cmdBtn.btn);
        }
    }
}

static void actionGetEncoder(void)
{
    int8_t encVal = inputGetEncoder();

    if (encVal) {
        actionSet(ACTION_ENCODER, encVal);
    }
}

static bool isRemoteCmdRepeatable(RcCmd cmd)
{
    ScreenType scrMode = ampGet()->screen;
    AudioProc *aProc = audioGet();
    InputType inType = amp.inType[aProc->par.input];

    switch (cmd) {
    case RC_CMD_VOL_UP:
    case RC_CMD_VOL_DOWN:
        return true;
    case RC_CMD_NAV_UP:
    case RC_CMD_NAV_DOWN:
        switch (scrMode) {
        case SCREEN_AUDIO_PARAM:
            return true;
        }
        break;
    case RC_CMD_NAV_LEFT:
    case RC_CMD_NAV_RIGHT:
        switch (scrMode) {
        case SCREEN_AUDIO_INPUT:
            if (inType == IN_TUNER) {
                return true;
            }
        }
        break;
    }

    return false;
}

static void actionGetRemote(void)
{
    RcData rcData = rcRead(true);
    static RcCmd cmdPrev = RC_CMD_END;

    if (rcData.ready) {
        swTimSet(SW_TIM_RC_NOACION, 200);

        RcCmd cmd = rcGetCmd(&rcData);
        int32_t repTime = swTimGet(SW_TIM_RC_REPEAT);

        if (cmd != cmdPrev) {
            actionSet(ACTION_REMOTE, (int16_t)cmd);
            swTimSet(SW_TIM_RC_REPEAT, 1000);
            cmdPrev = cmd;
        } else {
            if (isRemoteCmdRepeatable(cmd)) {
                if (repTime < 500) {
                    actionSet(ACTION_REMOTE, (int16_t)cmd);
                }
            } else {
                if (repTime == 0) {
                    actionSet(ACTION_REMOTE, (int16_t)cmd);
                    swTimSet(SW_TIM_RC_REPEAT, 1000);
                }
            }
        }
    } else {
        if (swTimGet(SW_TIM_RC_NOACION) == 0) {
            swTimSet(SW_TIM_RC_NOACION, SW_TIM_OFF);
            swTimSet(SW_TIM_RC_REPEAT, 0);
            cmdPrev = RC_CMD_END;
        }
    }
}

static void stbyTimerChange(void)
{
    int32_t stbyTimer = swTimGet(SW_TIM_STBY_TIMER);

    static const uint8_t stbyTimeMin[] = {
        2, 5, 10, 20, 40, 60, 90, 120, 180, 240,
    };

    for (uint8_t i = 0; i < sizeof (stbyTimeMin) / sizeof (stbyTimeMin[0]); i++) {
        int32_t stbyTime = 1000 * 60 * stbyTimeMin[i];
        if (stbyTimer < stbyTime) {
            swTimSet(SW_TIM_STBY_TIMER, stbyTime + 999);
            break;
        }
        if (i == sizeof (stbyTimeMin) / sizeof (stbyTimeMin[0]) - 1) {
            swTimSet(SW_TIM_STBY_TIMER, SW_TIM_OFF);
        }
    }
}

static void spModeChange(void)
{
    Spectrum *sp = spGet();

    sp->mode++;
    // Skip unused modes
    if (sp->mode > SP_MODE_MIXED && sp->mode < SP_MODE_WATERFALL) {
        sp->mode = SP_MODE_WATERFALL;
    }

    if (sp->mode >= (sp->peaks ? SP_MODE_END : SP_MODE_WATERFALL)) {
        sp->mode = SP_MODE_STEREO;
        sp->peaks = !sp->peaks;
        settingsStore(PARAM_SPECTRUM_PEAKS, sp->peaks);
    }

    amp.clearScreen = true;
    settingsStore(PARAM_SPECTRUM_MODE, sp->mode);
}

static void tunerSendMediaKey(MediaKey key)
{
    swTimSet(SW_TIM_RDS_HOLD, SW_TIM_OFF);
    switch (key) {
    case MEDIAKEY_PREV:
        tunerMove(TUNER_DIR_DOWN);
        break;
    case MEDIAKEY_NEXT:
        tunerMove(TUNER_DIR_UP);
        break;
    case MEDIAKEY_REWIND:
        tunerSeek(TUNER_DIR_DOWN);
        break;
    case MEDIAKEY_FFWD:
        tunerSeek(TUNER_DIR_UP);
        break;
    default:
        break;
    }
}

static void usbSendMediaKey(MediaKey key)
{
#ifdef _ENABLE_USB
    switch (key) {
    case MEDIAKEY_PREV:
        usbHidSendMediaKey(HIDMEDIAKEY_PREV_TRACK);
        break;
    case MEDIAKEY_NEXT:
        usbHidSendMediaKey(HIDMEDIAKEY_NEXT_TRACK);
        break;
    case MEDIAKEY_STOP:
        usbHidSendMediaKey(HIDMEDIAKEY_STOP);
        break;
    case MEDIAKEY_PLAY:
        usbHidSendMediaKey(HIDMEDIAKEY_PLAY);
        break;
    case MEDIAKEY_PAUSE:
        usbHidSendMediaKey(HIDMEDIAKEY_PAUSE);
        break;
    case MEDIAKEY_REWIND:
        usbHidSendMediaKey(HIDMEDIAKEY_REWIND);
        break;
    case MEDIAKEY_FFWD:
        usbHidSendMediaKey(HIDMEDIAKEY_FFWD);
        break;
    case MEDIAKEY_MUTE:
        usbHidSendMediaKey(HIDMEDIAKEY_MUTE);
        break;
    default:
        break;
    }
#else
    (void)key;
#endif
}

static void ampSendMediaKey(MediaKey key)
{
    AudioProc *aProc = audioGet();
    InputType inType = amp.inType[aProc->par.input];

    switch (inType) {
    case IN_TUNER:
        tunerSendMediaKey(key);
        break;
    case IN_PC:
        usbSendMediaKey(key);
        break;
    case IN_MPD:
    case IN_KARADIO:
        mpcSendMediaKey(key);
        break;
    case IN_BLUETOOTH:
        btSendMediaKey(key);
        break;
    default:
        break;
    }
}

static void actionGetTimers(void)
{
    if (swTimGet(SW_TIM_AMP_INIT) == 0) {
        actionSet(ACTION_INIT_HW, 0);
    } else if (swTimGet(SW_TIM_STBY_TIMER) == 0) {
        ampSendMediaKey(MEDIAKEY_STOP);
        actionSet(ACTION_STANDBY, FLAG_ENTER);
    } else if (swTimGet(SW_TIM_SILENCE_TIMER) == 0) {
        actionSet(ACTION_STANDBY, FLAG_ENTER);
    } else if (swTimGet(SW_TIM_RTC_INIT) == 0) {
        actionSet(ACTION_INIT_RTC, 0);
    } else if (swTimGet(SW_TIM_SOFT_VOLUME) == 0) {
        actionSet(ACTION_RESTORE_VOLUME, amp.volume);
    } else if (swTimGet(SW_TIM_DIGIT_INPUT) == 0) {
        actionSet(ACTION_FINISH_DIGIT_INPUT, 0);
    } else if (swTimGet(SW_TIM_DISPLAY) == 0) {
        actionSet(ACTION_DISP_EXPIRED, 0);
    }
}

static void actionRemapBtnShort(void)
{
    switch (action.value) {
    case BTN_D0:
        actionSet(ACTION_STANDBY, FLAG_SWITCH);
        break;
    case BTN_D1:
        actionSet(ACTION_AUDIO_INPUT_CHANGE, +1);
        break;
    case BTN_D2:
        actionSet(ACTION_NAVIGATE, RC_CMD_NAV_BACK);
        break;
    case BTN_D3:
        actionSet(ACTION_NAVIGATE, RC_CMD_CHAN_PREV);
        break;
    case BTN_D4:
        actionSet(ACTION_NAVIGATE, RC_CMD_CHAN_NEXT);
        break;
    case BTN_D5:
        actionSet(ACTION_NAVIGATE, RC_CMD_NAV_OK);
        break;
    case ENC_A:
        actionSet(ACTION_ENCODER, -1);
        break;
    case ENC_B:
        actionSet(ACTION_ENCODER, +1);
        break;
    default:
        break;
    }
}

static void actionRemapBtnLong(void)
{
    ScreenType scrMode = ampGet()->screen;
    AudioProc *aProc = audioGet();
    InputType inType = amp.inType[aProc->par.input];

    switch (action.value) {
    case BTN_D0:
        break;
    case BTN_D1:
        actionSet(ACTION_RTC_MODE, 0);
        break;
    case BTN_D2:
        switch (inType) {
        case IN_TUNER:
            if (scrMode == SCREEN_TEXTEDIT) {
                action.type = ACTION_TUNER_DEL_STATION;
            } else {
                action.type = ACTION_TUNER_EDIT_NAME;
            }
            break;
        case IN_BLUETOOTH:
            action.type = ACTION_BT_INPUT_CHANGE;
            break;
        default:
            break;
        }
        break;
    case BTN_D3:
        switch (inType) {
        case IN_TUNER:
            actionSet(ACTION_MEDIA, MEDIAKEY_REWIND);
            break;
        default:
            actionSet(ACTION_NAVIGATE, RC_CMD_CHAN_PREV);
            break;
        }
        break;
    case BTN_D4:
        switch (inType) {
        case IN_TUNER:
            actionSet(ACTION_MEDIA, MEDIAKEY_FFWD);
            break;
        default:
            actionSet(ACTION_NAVIGATE, RC_CMD_CHAN_NEXT);
            break;
        }
        break;
    case BTN_D5:
        switch (scrMode) {
        case SCREEN_TEXTEDIT:
            action.type = ACTION_OPEN_MENU;
            break;
        case SCREEN_STANDBY:
            actionSet(ACTION_MENU_SELECT, MENU_SETUP_SYSTEM);
            break;
        }
        break;
    case ENC_A:
        actionSet(ACTION_ENCODER, -1);
        break;
    case ENC_B:
        actionSet(ACTION_ENCODER, +1);
        break;
    default:
        break;
    }
}

static void actionRemapRemote(void)
{
    ScreenType scrMode = amp.screen;

    if (scrMode == SCREEN_MENU) {
        Menu *menu = menuGet();
        if ((menu->parent == MENU_SETUP_RC) && (menu->selected)) {
            actionSet(ACTION_MENU_CHANGE, 0);
            return;
        }
    }

    if (SCREEN_STANDBY == scrMode &&
        action.value == RC_CMD_MENU) {
        actionSet(ACTION_MENU_SELECT, MENU_SETUP_SYSTEM);
        return;
    }

    if (SCREEN_STANDBY == scrMode &&
        action.value != RC_CMD_STBY_SWITCH)
        return;

    switch (action.value) {
    case RC_CMD_STBY_SWITCH:
        actionSet(ACTION_STANDBY, FLAG_SWITCH);
        break;

    case RC_CMD_MUTE:
        actionSet(ACTION_AUDIO_MUTE, FLAG_SWITCH);
        break;
    case RC_CMD_VOL_UP:
        actionSet(ACTION_ENCODER, +1);
        break;
    case RC_CMD_VOL_DOWN:
        actionSet(ACTION_ENCODER, -1);
        break;

    case RC_CMD_MENU:
        action.type = ACTION_OPEN_MENU;
        break;

    case RC_CMD_CHAN_NEXT:
        actionSet(ACTION_MEDIA, MEDIAKEY_NEXT);
        break;
    case RC_CMD_CHAN_PREV:
        actionSet(ACTION_MEDIA, MEDIAKEY_PREV);
        break;

    case RC_CMD_DIG_0:
    case RC_CMD_DIG_1:
    case RC_CMD_DIG_2:
    case RC_CMD_DIG_3:
    case RC_CMD_DIG_4:
    case RC_CMD_DIG_5:
    case RC_CMD_DIG_6:
    case RC_CMD_DIG_7:
    case RC_CMD_DIG_8:
    case RC_CMD_DIG_9:
        actionSet(ACTION_DIGIT_INPUT, action.value - RC_CMD_DIG_0);
        break;

    case RC_CMD_IN_NEXT:
        actionSet(ACTION_AUDIO_INPUT_CHANGE, +1);
        break;

    case RC_CMD_NAV_OK:
    case RC_CMD_NAV_BACK:
    case RC_CMD_NAV_RIGHT:
    case RC_CMD_NAV_UP:
    case RC_CMD_NAV_LEFT:
    case RC_CMD_NAV_DOWN:
        actionSet(ACTION_NAVIGATE, action.value);
        break;

    case RC_CMD_BASS_UP:
        ampSelectTune(AUDIO_TUNE_BASS);
        actionSet(ACTION_ENCODER, +1);
        break;
    case RC_CMD_BASS_DOWN:
        ampSelectTune(AUDIO_TUNE_BASS);
        actionSet(ACTION_ENCODER, -1);
        break;
    case RC_CMD_MIDDLE_UP:
        ampSelectTune(AUDIO_TUNE_MIDDLE);
        actionSet(ACTION_ENCODER, +1);
        break;
    case RC_CMD_MIDDLE_DOWN:
        ampSelectTune(AUDIO_TUNE_MIDDLE);
        actionSet(ACTION_ENCODER, -1);
        break;
    case RC_CMD_TREBLE_UP:
        ampSelectTune(AUDIO_TUNE_TREBLE);
        actionSet(ACTION_ENCODER, +1);
        break;
    case RC_CMD_TREBLE_DOWN:
        ampSelectTune(AUDIO_TUNE_TREBLE);
        actionSet(ACTION_ENCODER, -1);
        break;

    case RC_CMD_LOUDNESS:
        actionSet(ACTION_AUDIO_LOUDNESS, FLAG_SWITCH);
        break;
    case RC_CMD_SURROUND:
        actionSet(ACTION_AUDIO_SURROUND, FLAG_SWITCH);
        break;
    case RC_CMD_EFFECT_3D:
        actionSet(ACTION_AUDIO_EFFECT3D, FLAG_SWITCH);
        break;
    case RC_CMD_TONE_BYPASS:
        actionSet(ACTION_AUDIO_BYPASS, FLAG_SWITCH);
        break;

    case RC_CMD_TIME:
        actionSet(ACTION_RTC_MODE, 0);
        break;

    case RC_CMD_STOP:
        actionSet(ACTION_MEDIA, MEDIAKEY_STOP);
        break;
    case RC_CMD_PLAY_PAUSE:
        actionSet(ACTION_MEDIA, MEDIAKEY_PLAY);
        break;
    case RC_CMD_REW:
        actionSet(ACTION_MEDIA, MEDIAKEY_REWIND);
        break;
    case RC_CMD_FWD:
        actionSet(ACTION_MEDIA, MEDIAKEY_FFWD);
        break;
    case RC_CMD_TIMER:
        actionSet(ACTION_TIMER, 0);
        break;
    case RC_CMD_SP_MODE:
        actionSet(ACTION_SP_MODE, 0);
        break;
    case RC_CMD_SCR_DEF:
        actionSet(ACTION_SCR_DEF, 0);
        break;
    case RC_CMD_BT_IN_NEXT:
        actionSet(ACTION_BT_INPUT_CHANGE, +1);
        break;
    default:
        break;
    }
}

static void actionRemapNavigate(void)
{
    ScreenType scrMode = ampGet()->screen;

    switch (scrMode) {
    case SCREEN_MENU:
        actionNavigateMenu((RcCmd)action.value);
        break;
    case SCREEN_TEXTEDIT:
        actionNavigateTextEdit((RcCmd)action.value);
        break;
    default:
        actionNavigateCommon((RcCmd)action.value);
        break;
    }
}

static void actionRemapEncoder(void)
{
    ScreenType scrMode = ampGet()->screen;
    AudioProc *aProc = audioGet();

    if (SCREEN_STANDBY == scrMode)
        return;

    int16_t encCnt = action.value;

    switch (scrMode) {
    case SCREEN_TIME:
        if (rtcGetMode() == RTC_NOEDIT) {
            actionSet(ACTION_AUDIO_PARAM_CHANGE, encCnt);
        } else {
            actionSet(ACTION_RTC_CHANGE, encCnt);
        }
        break;
    case SCREEN_MENU:
        actionSet(ACTION_MENU_CHANGE, encCnt);
        break;
    case SCREEN_TEXTEDIT:
        actionSet(ACTION_TEXTEDIT_CHANGE, encCnt);
        break;
    default:
        actionSet(ACTION_AUDIO_PARAM_CHANGE, encCnt);
        break;
    }

    if (ACTION_AUDIO_PARAM_CHANGE == action.type) {
        amp.screen = SCREEN_AUDIO_PARAM;
        switch (scrMode) {
        case SCREEN_SPECTRUM:
        case SCREEN_AUDIO_FLAG:
        case SCREEN_AUDIO_INPUT:
            aProc->tune = AUDIO_TUNE_VOLUME;
            break;
        default:
            break;
        }
    }
}

static void actionRemapCommon(void)
{
    ScreenType scrMode = ampGet()->screen;
    AudioProc *aProc = audioGet();

    switch (action.type) {
    case ACTION_STANDBY:
        if (scrMode == SCREEN_MENU) {
            action.value = FLAG_ENTER;
        } else if (FLAG_SWITCH == action.value) {
            switch (amp.status) {
            case AMP_STATUS_STBY:
                action.value = FLAG_EXIT;
                break;
            case AMP_STATUS_ACTIVE:
                action.value = FLAG_ENTER;
                break;
            default:
                actionSet(ACTION_NONE, 0);
                break;
            }
        }
        break;
    case ACTION_OPEN_MENU:
        switch (scrMode) {
        case SCREEN_TEXTEDIT:
            action.type = ACTION_TEXTEDIT_APPLY;
            break;
        case SCREEN_MENU:
            actionSet(ACTION_NAVIGATE, RC_CMD_NAV_OK);
            break;
        }
        break;
    case ACTION_AUDIO_MUTE:
        if (FLAG_SWITCH == action.value) {
            action.value = !aProc->par.mute;
        }
        break;
    case ACTION_AUDIO_LOUDNESS:
        if (FLAG_SWITCH == action.value) {
            action.value = !aProc->par.loudness;
        }
        break;
    case ACTION_AUDIO_SURROUND:
        if (FLAG_SWITCH == action.value) {
            action.value = !aProc->par.surround;
        }
        break;
    case ACTION_AUDIO_EFFECT3D:
        if (FLAG_SWITCH == action.value) {
            action.value = !aProc->par.effect3d;
        }
        break;
    case ACTION_AUDIO_BYPASS:
        if (FLAG_SWITCH == action.value) {
            action.value = !aProc->par.bypass;
        }
        break;
    default:
        break;
    }

    if (SCREEN_STANDBY == scrMode &&
        (ACTION_STANDBY != action.type &&
         ACTION_INIT_HW != action.type &&
         ACTION_REMOTE != action.type &&
         ACTION_INIT_RTC != action.type &&
         ACTION_MENU_SELECT != action.type)) {
        actionSet(ACTION_NONE, 0);
    }

    if (SCREEN_MENU == scrMode &&
        (ACTION_STANDBY != action.type &&
         ACTION_INIT_HW != action.type &&
         ACTION_NAVIGATE != action.type &&
         ACTION_MENU_CHANGE != action.type &&
         ACTION_MENU_SELECT != action.type &&
         ACTION_ENCODER != action.type)) {
        actionSet(ACTION_NONE, 0);
    }
}

void ampInitMuteStby(void)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
#ifdef STM32F3
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
#endif

    GPIO_InitStruct.Pin = MUTE_Pin;
    LL_GPIO_Init(MUTE_Port, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = STBY_Pin;
    LL_GPIO_Init(STBY_Port, &GPIO_InitStruct);

    ampPinMute(true);
    ampPinStby(true);
}

void ampSelectTune(AudioTune tune)
{
    amp.screen = SCREEN_AUDIO_PARAM;

    AudioProc *aProc = audioGet();
    if (aProc->tune != tune) {
        amp.clearScreen = true;
        aProc->tune = tune;
    }
}

void ampInit(void)
{
    utilEnableSwd(true);

    dbgInit();

    settingsInit();
    menuInit();

    ampInitMuteStby();
    pinsInit();
    rtcInit();

    labelsInit();
    canvasInit();

    spInit();

    inputInit();
    rcInit();

    controlInit();
    mpcInit();

    ampReadSettings();

    timerInit(TIM_SPECTRUM, 99, 35); // 20kHz timer:Dsplay IRQ/PWM and ADC conversion trigger
    swTimInit();

    rdsParserSetCb(rdsParserCb);

    inputSetPower(false);    // Power off input device

    swTimSet(SW_TIM_RTC_INIT, 500);

#ifdef _ENABLE_USB
    usbHidInit();
#endif

    amp.status = AMP_STATUS_STBY;
    controlReportAmpStatus();
}

void ampRun(void)
{
    while (1) {
        utilEnableSwd(SCREEN_STANDBY == amp.screen);

        controlGetData();
        mpcGetData();
        btReleaseKey();

        ampActionGet();
        ampActionRemap();
        ampActionHandle();

        ampScreenShow();
    }
}

Amp *ampGet(void)
{
    return &amp;
}

void ampActionQueue(ActionType type, int16_t value)
{
    actionSet(type, value);
}

static void ampActionGet(void)
{
    if (ACTION_NONE == action.type) {
        actionGetButtons();
    }

    if (ACTION_NONE == action.type) {
        actionGetEncoder();
    }

    if (ACTION_NONE == action.type) {
        actionGetRemote();
    }

    if (ACTION_NONE == action.type) {
        ScreenType scrMode = ampGet()->screen;

        if (scrMode == SCREEN_STANDBY && rtcCheckAlarm()) {
            actionSet(ACTION_STANDBY, FLAG_EXIT);
        }
    }

    if (ACTION_NONE == action.type) {
        actionGetTimers();
    }
}

static void ampActionRemap(void)
{
    switch (action.type) {
    case ACTION_BTN_SHORT:
        actionRemapBtnShort();
        break;
    case ACTION_BTN_LONG:
        actionRemapBtnLong();
        break;
    case ACTION_REMOTE:
        actionRemapRemote();
        break;
    default:
        break;
    }

    actionRemapCommon();

    if (ACTION_NAVIGATE == action.type) {
        actionRemapNavigate();
    }

    if (ACTION_ENCODER == action.type) {
        actionRemapEncoder();
    }
}


static void ampActionHandle(void)
{
    ScreenType scrMode = amp.screen;

    AudioProc *aProc = audioGet();
    InputType inType = amp.inType[aProc->par.input];
    Tuner *tuner = tunerGet();
    int8_t stNum = stationGetNum(tuner->status.freq);

    Canvas *canvas = canvasGet();

    switch (action.type) {
    case ACTION_INIT_HW:
        ampInitHw();
        actionResetSilenceTimer();
        break;
    case ACTION_INIT_RTC:
        rtcInit();
        break;
    case ACTION_STANDBY:
        if (action.value == FLAG_EXIT) {
            ampExitStby();
            screenSet(SCREEN_TIME, 1000);
        } else {
            ampEnterStby();
            actionDispExpired(SCREEN_STANDBY);
        }
        break;
    case ACTION_DISP_EXPIRED:
        actionDispExpired(scrMode);
        break;

    case ACTION_DIGIT_INPUT:
        if (scrMode == SCREEN_TIME) {
            rtcEditTime(rtcGetMode(), (int8_t)(action.value));
            screenSet(SCREEN_TIME, 5000);
        } else if (inType == IN_KARADIO) {
            swTimSet(SW_TIM_DIGIT_INPUT, 1000);
            mpcSendDigit((uint8_t)action.value);
            screenSet(SCREEN_AUDIO_INPUT, 1000);
        }
        break;
    case  ACTION_FINISH_DIGIT_INPUT:
        swTimSet(SW_TIM_DIGIT_INPUT, SW_TIM_OFF);
        if (inType == IN_KARADIO) {
            mpcFinishDigitInput();
            screenSet(SCREEN_AUDIO_INPUT, 1000);
        }
        break;

    case ACTION_MEDIA:
        switch (action.value) {

        case MEDIAKEY_PREV:
            amp.iconHint = ICON_PREV_TRACK;
            break;
        case MEDIAKEY_NEXT:
            amp.iconHint = ICON_NEXT_TRACK;
            break;
        case MEDIAKEY_STOP:
            amp.iconHint = ICON_STOP;
            break;
        case MEDIAKEY_PLAY:
            amp.iconHint = ICON_PLAY_PAUSE;
            break;
        case MEDIAKEY_PAUSE:
            break;
        case MEDIAKEY_REWIND:
            amp.iconHint = ICON_REWIND;
            break;
        case MEDIAKEY_FFWD:
            amp.iconHint = ICON_FFWD;
            break;
        }

        ampSendMediaKey((MediaKey)action.value);

        switch (inType) {
        case IN_TUNER:
            if (NULL == tuner->api) {
                amp.iconHint = ICON_EMPTY;
            }
        case IN_PC:
        case IN_MPD:
        case IN_KARADIO:
        case IN_BLUETOOTH:
            screenSet(SCREEN_AUDIO_INPUT, 800);
            break;
        default:
            amp.iconHint = ICON_EMPTY;
            break;
        }
        break;

    case ACTION_OPEN_MENU:
        if (scrMode == SCREEN_AUDIO_PARAM) {
            amp.clearScreen = true;
            actionNextAudioParam(aProc);
        } else {
            aProc->tune = AUDIO_TUNE_VOLUME;
        }
        screenSet(SCREEN_AUDIO_PARAM, 5000);
        break;

    case ACTION_RTC_MODE:
        if (scrMode == SCREEN_TIME) {
            rtcChangeMode(+1);
        } else {
            rtcSetMode(RTC_NOEDIT);
        }
        screenSet(SCREEN_TIME, rtcGetMode() == RTC_NOEDIT ? 5000 : 30000);
        break;
    case ACTION_RTC_CHANGE:
        if (action.value < 0) {
            rtcChangeTime(rtcGetMode(), -1);
        } else if (action.value > 0) {
            rtcChangeTime(rtcGetMode(), +1);
        }
        screenSet(scrMode, 5000);
        break;
    case ACTION_RTC_SET_HOUR:
    case ACTION_RTC_SET_MIN:
    case ACTION_RTC_SET_SEC:
    case ACTION_RTC_SET_DATE:
    case ACTION_RTC_SET_MONTH:
    case ACTION_RTC_SET_YEAR:
        rtcSetTime((RtcMode)(action.type - ACTION_RTC_SET_HOUR), (int8_t)(action.value));
        screenSet(scrMode, 5000);
        break;

    case ACTION_AUDIO_INPUT_CHANGE:
        if (scrMode == SCREEN_AUDIO_INPUT) {
            actionSetInput(actionGetNextAudioInput((int8_t)action.value));
        }
        actionPostSetInput();
        break;
    case ACTION_AUDIO_INPUT_SET:
        actionSetInput((int8_t)action.value);
        actionPostSetInput();
        break;
    case ACTION_AUDIO_PARAM_CHANGE:
        audioChangeTune(aProc->tune, (int8_t)(action.value));
        if (aProc->tune == AUDIO_TUNE_VOLUME) {
            amp.volume = aProc->par.tune[AUDIO_TUNE_VOLUME].value;
        }
        if (aProc->par.mute) {
            ampMute(false);
        }
        screenSet(SCREEN_AUDIO_PARAM, 3000);
        controlReportAudioTune(aProc->tune);
        swTimSet(SW_TIM_SOFT_VOLUME, SW_TIM_OFF);
        break;
    case ACTION_AUDIO_PARAM_SET:
        audioSetTune(aProc->tune, (int8_t)action.value);
        screenSet(SCREEN_AUDIO_PARAM, 3000);
        controlReportAudioTune(aProc->tune);
        swTimSet(SW_TIM_SOFT_VOLUME, SW_TIM_OFF);
        break;

    case ACTION_AUDIO_MUTE:
        ampMute(action.value);
        if (aProc->tune != AUDIO_FLAG_MUTE) {
            amp.clearScreen = true;
        }
        aProc->tune = AUDIO_FLAG_MUTE;
        screenSet(SCREEN_AUDIO_FLAG, 3000);
        break;
    case ACTION_AUDIO_LOUDNESS:
        audioSetLoudness(action.value);
        if (aProc->tune != AUDIO_FLAG_LOUDNESS) {
            amp.clearScreen = true;
        }
        aProc->tune = AUDIO_FLAG_LOUDNESS;
        screenSet(SCREEN_AUDIO_FLAG, 3000);
        break;
    case ACTION_AUDIO_SURROUND:
        audioSetSurround(action.value);
        if (aProc->tune != AUDIO_FLAG_SURROUND) {
            amp.clearScreen = true;
        }
        aProc->tune = AUDIO_FLAG_SURROUND;
        screenSet(SCREEN_AUDIO_FLAG, 3000);
        break;
    case ACTION_AUDIO_EFFECT3D:
        audioSetEffect3D(action.value);
        if (aProc->tune != AUDIO_FLAG_EFFECT3D) {
            amp.clearScreen = true;
        }
        aProc->tune = AUDIO_FLAG_EFFECT3D;
        screenSet(SCREEN_AUDIO_FLAG, 3000);
        break;
    case ACTION_AUDIO_BYPASS:
        audioSetBypass(action.value);
        if (aProc->tune != AUDIO_FLAG_BYPASS) {
            amp.clearScreen = true;
        }
        aProc->tune = AUDIO_FLAG_BYPASS;
        screenSet(SCREEN_AUDIO_FLAG, 3000);
        break;

    case ACTION_RESTORE_VOLUME:
        if (aProc->par.tune[AUDIO_TUNE_VOLUME].value < action.value) {
            audioChangeTune(AUDIO_TUNE_VOLUME, +1);
            swTimSet(SW_TIM_SOFT_VOLUME, 25);
        } else {
            swTimSet(SW_TIM_SOFT_VOLUME, SW_TIM_OFF);
        }
        break;

    case ACTION_BT_INPUT_CHANGE:
        btNextInput();
        amp.iconHint = ICON_EMPTY;
        screenSet(SCREEN_AUDIO_INPUT, 5000);
        break;

    case ACTION_TUNER_SET_FREQ:
        if (inType == IN_TUNER) {
            swTimSet(SW_TIM_RDS_HOLD, SW_TIM_OFF);
            tunerSetFreq((uint16_t)action.value);
            screenSet(SCREEN_AUDIO_INPUT, 2000);
        }
        break;

    case ACTION_TUNER_EDIT_NAME:
        canvas->te.name = labelsGet(LABEL_TUNER_FM_STATION_NAME);
        textEditSet(&canvas->te, stationGetName(stNum), STATION_NAME_MAX_LEN, STATION_NAME_MAX_SYM);
        screenSet(SCREEN_TEXTEDIT, 10000);
        break;
    case ACTION_TUNER_DEL_STATION:
        stationRemove(tuner->status.freq);
        screenSet(SCREEN_AUDIO_INPUT, 2000);
        break;

    case ACTION_TEXTEDIT_CHANGE:
        textEditChange(&canvas->te, (int8_t)action.value);
        screenSet(SCREEN_TEXTEDIT, 10000);
        break;
    case ACTION_TEXTEDIT_ADD_CHAR:
        textEditAddChar(&canvas->te);
        screenSet(SCREEN_TEXTEDIT, 10000);
        break;
    case ACTION_TEXTEDIT_DEL_CHAR:
        textEditDelChar(&canvas->te);
        screenSet(SCREEN_TEXTEDIT, 10000);
        break;
    case ACTION_TEXTEDIT_APPLY:
        stationStore(tuner->status.freq, canvas->te.str);
        screenSet(SCREEN_AUDIO_INPUT, 2000);
        break;
    case ACTION_TEXTEDIT_CANCEL:
        screenSet(SCREEN_AUDIO_INPUT, 2000);
        break;

    case ACTION_MENU_SELECT: {
        MenuIdx parent = menuGet()->parent;
        menuSetActive((MenuIdx)action.value);
        if (parent != menuGet()->parent) {
            amp.clearScreen = true;
        }
        screenSet(SCREEN_MENU, 10000);
        break;
    }
    case ACTION_MENU_CHANGE:
        menuChange((int8_t)action.value);
        screenSet(SCREEN_MENU, 10000);
        break;

    case ACTION_TIMER:
        if (scrMode == SCREEN_STBY_TIMER) {
            stbyTimerChange();
        }
        screenSet(SCREEN_STBY_TIMER, 5000);
        break;
    case ACTION_SP_MODE:
        if (scrMode == SCREEN_SPECTRUM) {
            spModeChange();
        }
        screenSet(SCREEN_SPECTRUM, 3000);
        break;
    case ACTION_SCR_DEF:
        rtcSetMode(RTC_NOEDIT);
        if (scrMode == amp.defScreen) {
            if (++amp.defScreen >= SCREEN_STANDBY) {
                amp.defScreen = SCREEN_SPECTRUM;
            }
        }
        screenSet(amp.defScreen, 3000);
        break;
    default:
        break;
    }

    // Reset silence timer on any user action
    if (action.type != ACTION_NONE && action.type != ACTION_DISP_EXPIRED) {
        actionResetSilenceTimer();
    }

    // Reset silence timer on signal
    if (scrMode != SCREEN_STANDBY) {
        if (spCheckSignal()) {
            actionResetSilenceTimer();
        }
    }

    if (action.type != ACTION_NONE) {
        amp.screen = screen.type;
    }

    if (screen.timeout > 0) {
        swTimSet(SW_TIM_DISPLAY, screen.timeout);
    } else if (screen.timeout == 0) {
        swTimSet(SW_TIM_DISPLAY, SW_TIM_OFF);
    }

    action.type = ACTION_NONE;
    screen.timeout = SW_TIM_OFF;
}

void ampScreenShow(void)
{
    GlcdRect rect = canvasGet()->layout->rect;
    AudioProc *aProc = audioGet();
    InputType inType = amp.inType[aProc->par.input];

    glcdSetRect(&rect);

    bool clear = screenCheckClear();
    if (amp.screen == SCREEN_TEXTEDIT) {
        GlcdRect teRect = canvasGet()->layout->textEdit.rect;
        if (clear) {
            const int16_t th = rect.h / 100;
            glcdDrawFrame(teRect.x - rect.x - th, teRect.y - rect.y - th, teRect.w + 2 * th, teRect.h + 2 * th,
                          th, canvasGet()->pal->fg);
        }
        glcdSetRect(&teRect);
    }

    if (amp.screen != SCREEN_STANDBY) {
        if (inType == IN_TUNER) {
            if (swTimGet(SW_TIM_INPUT_POLL) == 0) {
                tunerUpdateStatus();
                controlReportTunerFreq(false);
                swTimSet(SW_TIM_INPUT_POLL, 100);
            }
            if (swTimGet(SW_TIM_RDS_HOLD) == 0) {
                rdsParserReset();
                swTimSet(SW_TIM_RDS_HOLD, SW_TIM_OFF);
            }
        }
    }

    if (clear) {
        canvasClear();
    }

    switch (amp.screen) {
    case SCREEN_STANDBY:
    case SCREEN_TIME:
        canvasShowTime(clear);
        break;
    case SCREEN_SPECTRUM:
        canvasShowSpectrum(clear);
        break;
    case SCREEN_SAVER:
        canvasShowStars(clear, 0);
        break;
    case SCREEN_AUDIO_PARAM:
        canvasShowTune(clear);
        break;
    case SCREEN_AUDIO_FLAG:
        canvasShowAudioFlag(clear);
        break;
    case SCREEN_AUDIO_INPUT:
        canvasShowAudioInput(clear, amp.iconHint);
        break;
    case SCREEN_MENU:
        canvasShowMenu(clear);
        break;
    case SCREEN_TEXTEDIT:
        canvasShowTextEdit(clear);
        break;
    case SCREEN_STBY_TIMER:
        canvasShowTimer(clear, swTimGet(SW_TIM_STBY_TIMER));
        break;
    case SCREEN_SILENCE_TIMER:
        canvasShowTimer(clear, swTimGet(SW_TIM_SILENCE_TIMER));
        break;
    default:
        break;
    }

    canvasDebugFPS();
}

void ampSetBrightness(int8_t value)
{
    amp.brightness = value;
}

void TIM_SPECTRUM_HANDLER(void)
{
    if (LL_TIM_IsActiveFlag_UPDATE(TIM_SPECTRUM)) {
        // Clear the update interrupt flag
        LL_TIM_ClearFlag_UPDATE(TIM_SPECTRUM);

        // Callbacks
        ampScreenPwm();
        spConvertADC();
    }
}
