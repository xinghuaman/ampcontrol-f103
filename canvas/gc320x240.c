#include "canvas.h"

static void showParam(DispParam *dp);
static void showSpectrum(bool clear, SpectrumData *spData);
static void showTuner(DispTuner *dt);

static const CanvasParam canvasParam;

static Canvas canvas = {
    .width = 320,
    .height = 240,
    .showParam = showParam,
    .showSpectrum = showSpectrum,
    .showTuner = showTuner,

    .par = &canvasParam,
};

static const CanvasParam canvasParam = {
    .time.hmsFont = &fontterminusdig80,
    .time.dmyFont = &fontterminusdig64,
    .time.wdFont = &fontterminusmod32x2,
    .time.hmsY = 10,
    .time.dmyY = 100,
    .time.wdY = 170,

    .bar.sc = 80,
    .bar.sw = 2,
    .bar.pos = 60,
    .bar.half = 10,
    .bar.middle = 2,

    .menu.headFont = &fontterminus28b,
    .menu.menuFont = &fontterminus22b,
    .menu.itemCnt = 8,
};

void gc320x240Init(Canvas **value)
{
    *value = &canvas;
    menuGet()->dispSize = canvas.par->menu.itemCnt;
}

static void showParam(DispParam *dp)
{
    glcdSetFont(&fontterminusmod24x2);
    glcdSetFontColor(LCD_COLOR_WHITE);

    glcdSetXY(0, 0);
    glcdWriteString((char *)dp->label);

    canvasDrawBar(dp->value, dp->min, dp->max);

    glcdSetXY(canvas.width, 176);
    glcdSetFontAlign(FONT_ALIGN_RIGHT);
    glcdSetFont(&fontterminusmod24x2);
    glcdWriteNum((dp->value * dp->step) / 8, 3, ' ', 10);

    glcdSetXY(canvas.width - 48, 0);
    glcdWriteIcon(dp->icon, &iconsamp48, LCD_COLOR_AQUA, canvas.color);
}

static void showSpectrum(bool clear, SpectrumData *spData)
{
    const uint8_t step = 3;     // Step in pixels between spectrum columns
    const uint8_t oft = 0;      // Offset of spectrum column inside step

    const uint8_t width = 2;    // Width of spectrum column

    canvasShowSpectrum(clear, spData, step, oft, width);
}

static void showTuner(DispTuner *dt)
{
    const tFont *fmFont = &fontterminusmod32x2;

    canvasShowTuner(dt, fmFont);
}
