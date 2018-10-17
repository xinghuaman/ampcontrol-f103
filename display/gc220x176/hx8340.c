#include "hx8340.h"

#include "../dispdrv.h"
#include "../../pins.h"
#include "../../functions.h"

#define HX8340_WIDTH           176
#define HX8340_HEIGHT          220
#define HX8340_PIXELS          (HX8340_WIDTH * HX8340_HEIGHT)

static GlcdDriver glcd = {
    .clear = hx8340Clear,
    .drawPixel = hx8340DrawPixel,
    .drawRectangle = hx8340DrawRectangle,
    .drawImage = hx8340DrawImage,
};

static inline void hx8340SelectReg(uint8_t reg) __attribute__((always_inline));
static inline void hx8340SelectReg(uint8_t reg)
{
    CLR(DISP_8BIT_RS);
    dispdrvSendData8(reg);
    SET(DISP_8BIT_RS);
}

static void hx8340WriteReg(uint8_t reg, uint8_t dataR)
{
    hx8340SelectReg(reg);
    dispdrvSendData8(dataR);
}

static inline void hx8340InitSeq(void)
{
    // Wait for reset
    _delay_ms(50);

    CLR(DISP_8BIT_CS);

    // Initial Sequence
    //Driving ability Setting
    hx8340WriteReg(0x60, 0x00); //PTBA[15:8]
    hx8340WriteReg(0x61, 0x06); //PTBA[15:8]
    hx8340WriteReg(0x62, 0x00); //STBA[15:8]
    hx8340WriteReg(0x63, 0xC8); //STBA[7:0]
    hx8340WriteReg(0x73, 0x70); //OPON[7:0],SET OPON=70h, default 38h

    //Gamma 2.2 Setting
    hx8340WriteReg(0x40, 0x00);
    hx8340WriteReg(0x41, 0x40);
    hx8340WriteReg(0x42, 0x45);
    hx8340WriteReg(0x43, 0x01);
    hx8340WriteReg(0x44, 0x60);
    hx8340WriteReg(0x45, 0x05);
    hx8340WriteReg(0x46, 0x0C);
    hx8340WriteReg(0x47, 0xD1);
    hx8340WriteReg(0x48, 0x05);
    hx8340WriteReg(0x50, 0x75);
    hx8340WriteReg(0x51, 0x01);
    hx8340WriteReg(0x52, 0x67);
    hx8340WriteReg(0x53, 0x14);
    hx8340WriteReg(0x54, 0xF2);
    hx8340WriteReg(0x55, 0x07);
    hx8340WriteReg(0x56, 0x03);
    hx8340WriteReg(0x57, 0x49);

    //Power Voltage Setting
    hx8340WriteReg(0x1F, 0x03); //VRH=4.65V
    hx8340WriteReg(0x20, 0x00); //BT (VGH~15V,VGL~-12V,DDVDH~5V)
    hx8340WriteReg(0x24, 0x1C); //VMH(VCOM High voltage3.2V)
    hx8340WriteReg(0x25, 0x34); //VML(VCOM Low voltage -1.2V)

    //****VCOM offset**///
    hx8340WriteReg(0x23, 0x2F);

    //Power on Setting
    hx8340WriteReg(0x18, 0x44); //I/P_RADJ,N/P_RADJ, Normal mode 60Hz
    hx8340WriteReg(0x21, 0x01); //OSC_EN='1', start Osc
    hx8340WriteReg(0x01, 0x00); //SLP='0', out sleep
    hx8340WriteReg(0x1C, 0x03); //AP=011
    hx8340WriteReg(0x19, 0x06); // VOMG=1,PON=1, DK=0,
    _delay_ms(5);

    //Display ON Setting
    hx8340WriteReg(0x26, 0x84); //PT=10,GON=0, DTE=0, D=0100
    _delay_ms(40);
    hx8340WriteReg(0x26, 0xB8); //PT=10,GON=1, DTE=1, D=1000
    _delay_ms(40);
    hx8340WriteReg(0x26, 0xBC); //PT=10,GON=1, DTE=1, D=1100

    //Set GRAM Area
    hx8340WriteReg(0x02, 0x00); //Column Start
    hx8340WriteReg(0x03, 0x00);
    hx8340WriteReg(0x04, 0x00); //Column End
    hx8340WriteReg(0x05, 0xAF);
    hx8340WriteReg(0x06, 0x00); //Row Start
    hx8340WriteReg(0x07, 0x00);
    hx8340WriteReg(0x08, 0x00); //Row End
    hx8340WriteReg(0x09, 0xDB);

    hx8340WriteReg(0x17, 0x05);

    hx8340WriteReg(0x16, 0x48);

    SET(DISP_8BIT_CS);
}

static inline void hx8340SetWindow(uint16_t x, uint16_t y, uint16_t w,
                                   uint16_t h) __attribute__((always_inline));
static inline void hx8340SetWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    hx8340WriteReg(0x03, y);
    hx8340WriteReg(0x05, y + h - 1);

    hx8340WriteReg(0x07, x);
    hx8340WriteReg(0x09, x + w - 1);

    hx8340SelectReg(0x22);
}

void hx8340Init(GlcdDriver **driver)
{
    *driver = &glcd;
    gc220x176Init(*driver);

    SET(DISP_8BIT_LED);
    SET(DISP_8BIT_RD);
    SET(DISP_8BIT_WR);
    SET(DISP_8BIT_RS);
    SET(DISP_8BIT_CS);

    CLR(DISP_8BIT_RST);
    _delay_ms(1);
    SET(DISP_8BIT_RST);

    hx8340InitSeq();
}

void hx8340Clear(void)
{
    hx8340DrawRectangle(0, 0, glcd.canvas->width, glcd.canvas->height, LCD_COLOR_BLACK);
}

void hx8340Sleep(void)
{
    CLR(DISP_8BIT_CS);

    hx8340WriteReg(0x26, 0xB8); //GON=’1’ DTE=’1’ D[1:0]=’10’
    _delay_ms(40);
    hx8340WriteReg(0x19, 0x01); //VCOMG=’0’, PON=’0’, DK=’1’
    _delay_ms(40);
    hx8340WriteReg(0x26, 0xA4); //GON=’1’ DTE=’0’ D[1:0]=’01’
    _delay_ms(40);
    hx8340WriteReg(0x26, 0x84); //GON=’0’ DTE=’0’ D[1:0]=’01’
    _delay_ms(40);
    hx8340WriteReg(0x1C, 0x00); //AP[2:0]=’000’
    hx8340WriteReg(0x01, 0x02); //SLP=’1’
    hx8340WriteReg(0x01, 0x00); //OSC_EN=’0’

    SET(DISP_8BIT_CS);
}

void hx8340Wakeup(void)
{
    CLR(DISP_8BIT_CS);

    hx8340WriteReg(0x18, 0x44); //I/P_RADJ,N/P_RADJ, Normal mode 60Hz
    hx8340WriteReg(0x21, 0x01); //OSC_EN='1', start Osc
    hx8340WriteReg(0x01, 0x00); //SLP='0', out sleep
    hx8340WriteReg(0x1C, 0x03); //AP=011
    hx8340WriteReg(0x19, 0x06); // VOMG=1,PON=1, DK=0,
    _delay_ms(5);
    hx8340WriteReg(0x26, 0x84); //PT=10,GON=0, DTE=0, D=0100
    _delay_ms(40);
    hx8340WriteReg(0x26, 0xB8); //PT=10,GON=1, DTE=1, D=1000
    _delay_ms(40);
    hx8340WriteReg(0x26, 0xBC); //PT=10,GON=1, DTE=1, D=1100

    SET(DISP_8BIT_CS);
}

void hx8340DrawPixel(int16_t x, int16_t y, uint16_t color)
{
    CLR(DISP_8BIT_CS);

    hx8340SetWindow(x, y, 1, 1);
    dispdrvSendData16(color);

    SET(DISP_8BIT_CS);
}

void hx8340DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
    CLR(DISP_8BIT_CS);

    hx8340SetWindow(x, y, w, h);
    dispdrvSendFill(w * h, color);

    SET(DISP_8BIT_CS);
}

void hx8340DrawImage(tImage *img)
{
    uint16_t w = img->width;
    uint16_t h = img->height;
    uint16_t x0 = glcd.canvas->x;
    uint16_t y0 = glcd.canvas->y;

    CLR(DISP_8BIT_CS);

    hx8340SetWindow(x0, y0, w, h);
    dispdrvSendImage(img, w, h);

    SET(DISP_8BIT_CS);
}