#include "ili9327.h"

#include "../dispdrv.h"
#include "../../pins.h"
#include "../../functions.h"

#define ILI9327_WIDTH           240
#define ILI9327_HEIGHT          400
#define ILI9327_PIXELS          (ILI9327_WIDTH * ILI9327_HEIGHT)

static GlcdDriver glcd = {
    .clear = ili9327Clear,
    .drawPixel = ili9327DrawPixel,
    .drawRectangle = ili9327DrawRectangle,
    .drawImage = ili9327DrawImage,
};

static inline void ili9327SelectReg(uint8_t reg) __attribute__((always_inline));
static inline void ili9327SelectReg(uint8_t reg)
{
    CLR(DISP_8BIT_RS);
    dispdrvSendData8(reg);
    SET(DISP_8BIT_RS);
}

static inline void ili9327InitSeq(void)
{
    // Wait for reset
    _delay_ms(50);

    CLR(DISP_8BIT_CS);

    // Initial Sequence
    ili9327SelectReg(0xE9);
    dispdrvSendData8(0x20);

    ili9327SelectReg(0x11);
    _delay_ms(100);

    ili9327SelectReg(0xD1);
    dispdrvSendData8(0x00);
    dispdrvSendData8(0x71);
    dispdrvSendData8(0x19);

    ili9327SelectReg(0xD0);
    dispdrvSendData8(0x07);
    dispdrvSendData8(0x01);
    dispdrvSendData8(0x08);

    ili9327SelectReg(0x36);
    dispdrvSendData8(0x08);

    ili9327SelectReg(0x3A);
    dispdrvSendData8(0x05);

    ili9327SelectReg(0xC1);
    dispdrvSendData8(0x10);
    dispdrvSendData8(0x10);
    dispdrvSendData8(0x02);
    dispdrvSendData8(0x02);

    ili9327SelectReg(0xC0);
    dispdrvSendData8(0x00);
    dispdrvSendData8(0x35);
    dispdrvSendData8(0x00);
    dispdrvSendData8(0x00);
    dispdrvSendData8(0x01);
    dispdrvSendData8(0x02);

    ili9327SelectReg(0xC5);
    dispdrvSendData8(0x04);

    ili9327SelectReg(0xD2);
    dispdrvSendData8(0x01);
    dispdrvSendData8(0x44);

    ili9327SelectReg(0xC8);
    dispdrvSendData8(0x04);
    dispdrvSendData8(0x67);
    dispdrvSendData8(0x35);
    dispdrvSendData8(0x04);
    dispdrvSendData8(0x08);
    dispdrvSendData8(0x06);
    dispdrvSendData8(0x24);
    dispdrvSendData8(0x01);
    dispdrvSendData8(0x37);
    dispdrvSendData8(0x40);
    dispdrvSendData8(0x03);
    dispdrvSendData8(0x10);
    dispdrvSendData8(0x08);
    dispdrvSendData8(0x80);
    dispdrvSendData8(0x00);

    ili9327SelectReg(0x2A);
    dispdrvSendData8(0x00);
    dispdrvSendData8(0x00);
    dispdrvSendData8(0x00);
    dispdrvSendData8(0xEF);

    ili9327SelectReg(0x2B);
    dispdrvSendData8(0x00);
    dispdrvSendData8(0x00);
    dispdrvSendData8(0x01);
    dispdrvSendData8(0x8F);

    ili9327SelectReg(0x29);

    SET(DISP_8BIT_CS);
}

static inline void ili9327SetWindow(uint16_t x, uint16_t y, uint16_t w,
                                    uint16_t h) __attribute__((always_inline));
static inline void ili9327SetWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    ili9327SelectReg(0x2A);
    dispdrvSendData16(y);
    dispdrvSendData16(y + h - 1);

    ili9327SelectReg(0x2B);
    dispdrvSendData16(x);
    dispdrvSendData16(x + w - 1);

    ili9327SelectReg(0x2C);
}

void ili9327Init(GlcdDriver **driver)
{
    *driver = &glcd;
    gc400x240Init(*driver);

    SET(DISP_8BIT_LED);
    SET(DISP_8BIT_RD);
    SET(DISP_8BIT_WR);
    SET(DISP_8BIT_RS);
    SET(DISP_8BIT_CS);

    CLR(DISP_8BIT_RST);
    _delay_ms(1);
    SET(DISP_8BIT_RST);

    ili9327InitSeq();
}

void ili9327Clear(void)
{
    ili9327DrawRectangle(0, 0, glcd.canvas->width, glcd.canvas->height, LCD_COLOR_BLACK);
}

void ili9327Sleep(void)
{
    CLR(DISP_8BIT_CS);

    ili9327SelectReg(0x28);    // Display OFF
    _delay_ms(100);
    ili9327SelectReg(0x10);

    SET(DISP_8BIT_CS);
}

void ili9327Wakeup(void)
{
    CLR(DISP_8BIT_CS);

    ili9327SelectReg(0x11);    // Display ON
    _delay_ms(100);
    ili9327SelectReg(0x29);

    SET(DISP_8BIT_CS);
}

void ili9327DrawPixel(int16_t x, int16_t y, uint16_t color)
{
    CLR(DISP_8BIT_CS);

    ili9327SetWindow(x, y, 1, 1);
    dispdrvSendData16(color);

    SET(DISP_8BIT_CS);
}

void ili9327DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
    CLR(DISP_8BIT_CS);

    ili9327SetWindow(x, y, w, h);
    dispdrvSendFill(w * h, color);

    SET(DISP_8BIT_CS);
}

void ili9327DrawImage(tImage *img)
{
    uint16_t w = img->width;
    uint16_t h = img->height;
    uint16_t x0 = glcd.canvas->x;
    uint16_t y0 = glcd.canvas->y;

    CLR(DISP_8BIT_CS);

    ili9327SetWindow(x0, y0, w, h);
    dispdrvSendImage(img, w, h);

    SET(DISP_8BIT_CS);
}