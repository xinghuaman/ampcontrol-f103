#include "canvas.h"

// On 160x128 we can draw max 4 menu items + menu header
#define MENU_SIZE_VISIBLE   7

static void showTime(RTC_type *rtc, char *wday);
static void showParam(DispParam *dp);
static void showSpectrum(bool clear, SpectrumData *spData);
static void showTuner(DispTuner *dt);
static void showMenu(void);

static Canvas canvas = {
    .width = 160,
    .height = 128,
    .showTime = showTime,
    .showParam = showParam,
    .showSpectrum = showSpectrum,
    .showTuner = showTuner,
    .showMenu = showMenu,
};

static BarParams bar = {
    .sc = 80,
    .sw = 1,
    .pos = 40,
    .half = 8,
    .middle = 2,
};

void gc160x128Init(Canvas **value)
{
    *value = &canvas;
    menuGet()->dispSize = MENU_SIZE_VISIBLE;
}

static void displayTm(RTC_type *rtc, uint8_t tm)
{
    int8_t time = *((int8_t *)rtc + tm);

    glcdSetFontColor(LCD_COLOR_WHITE);
    glcdWriteChar(LETTER_SPACE_CHAR);
    if (rtc->etm == tm)
        glcdSetFontColor(LCD_COLOR_OLIVE);
    if (tm == RTC_YEAR) {
        glcdWriteString("20");
        glcdWriteChar(LETTER_SPACE_CHAR);
    }
    glcdWriteNum(time, 2, '0', 10);
    glcdSetFontColor(LCD_COLOR_WHITE);
    glcdWriteChar(LETTER_SPACE_CHAR);
}

static void drawShowBar(int16_t value, int16_t min, int16_t max)
{
    static const int16_t sc = 80; // Scale count
    static const uint8_t sw = 1; // Scale width

    if (min + max) { // Non-symmectic scale => rescale to 0..sl
        value = sc * (value - min) / (max - min);
    } else { // Symmetric scale => rescale to -sl/2..sl/2
        value = (sc / 2) * value / max;
    }

    for (uint16_t i = 0; i < sc; i++) {
        uint16_t color = LCD_COLOR_WHITE;

        if (min + max) { // Non-symmetric scale
            if (i >= value) {
                color = canvas.color;
            }
        } else { // Symmetric scale
            if ((value > 0 && i >= value + (sc / 2)) ||
                (value >= 0 && i < (sc / 2 - 1)) ||
                (value < 0 && i < value + (sc / 2)) ||
                (value <= 0 && i > (sc / 2))) {
                color = canvas.color;
            }
        }

        uint16_t width = canvas.width;

        glcdDrawRect(i * (width / sc) + 1, 34, sw, 6, color);
        glcdDrawRect(i * (width / sc) + 1, 40, sw, 2, LCD_COLOR_WHITE);
        glcdDrawRect(i * (width / sc) + 1, 42, sw, 6, color);
    }
}

static void showTime(RTC_type *rtc, char *wday)
{
    glcdSetXY(1, 8);
    glcdSetFont(&fontterminusdig40);

    displayTm(rtc, RTC_HOUR);
    glcdWriteChar(LETTER_SPACE_CHAR);
    glcdWriteChar(':');
    glcdWriteChar(LETTER_SPACE_CHAR);
    displayTm(rtc, RTC_MIN);
    glcdWriteChar(LETTER_SPACE_CHAR);
    glcdWriteChar(':');
    glcdWriteChar(LETTER_SPACE_CHAR);
    displayTm(rtc, RTC_SEC);

    glcdSetXY(2, 58);
    glcdSetFont(&fontterminusdig30);

    displayTm(rtc, RTC_DATE);
    glcdWriteChar(LETTER_SPACE_CHAR);
    glcdWriteChar('.');
    glcdWriteChar(LETTER_SPACE_CHAR);
    displayTm(rtc, RTC_MONTH);
    glcdWriteChar(LETTER_SPACE_CHAR);
    glcdWriteChar('.');
    glcdWriteChar(LETTER_SPACE_CHAR);
    displayTm(rtc, RTC_YEAR);

    glcdSetXY(80, 94);
    glcdSetFont(&fontterminus28);
    glcdSetFontColor(LCD_COLOR_AQUA);

    static char *wdayOld = 0;
    if (wday != wdayOld) {
        glcdDrawRect(0, 94, 160, 32, canvas.color);
    }

    glcdSetFontAlign(FONT_ALIGN_CENTER);
    glcdWriteString(wday);

    wdayOld = wday;
}

static void showParam(DispParam *dp)
{
    glcdSetFont(&fontterminus28);
    glcdSetFontColor(LCD_COLOR_WHITE);

    glcdSetXY(2, 0);
    glcdWriteString((char *)dp->label);

    drawShowBar(dp->value, dp->min, dp->max);

    glcdSetXY(157, 88);
    glcdSetFont(&fontterminusdig40);

    glcdSetFontAlign(FONT_ALIGN_RIGHT);
    glcdWriteNum((dp->value * dp->step) / 8, 3, ' ', 10);
}

static void showTuner(DispTuner *dt)
{
    const tFont *fmFont = &fontterminus32;

    canvasShowTuner(dt, fmFont, &bar);
}

static void showSpectrum(bool clear, SpectrumData *spData)
{
    const uint8_t step = 2;     // Step in pixels between spectrum columns
    const uint8_t oft = 0;      // Offset of spectrum column inside step

    const uint8_t width = 1;    // Width of spectrum column

    canvasShowSpectrum(clear, spData, step, oft, width);
}


static void showMenu(void)
{
    canvasShowMenu(&fontterminus14b, &fontterminus12);
}
