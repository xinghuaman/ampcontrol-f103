#ifndef DISPDRV_H
#define DISPDRV_H

#include "glcd.h"

#if defined (_KS0108)
#include "gm128x64/ks0108.h"
#elif defined (_ST7920)
#include "gm128x64/st7920.h"
#elif defined (_SSD1306)
#include "gm128x64/ssd1306.h"
#elif defined (_ILI9163)
#include "gc160x128/ili9163.h"
#elif defined (_ST7735)
#include "gc160x128/st7735.h"
#elif defined (_LS020)
#include "gc176x132/ls020.h"
#elif defined (_LPH9157)
#include "gc176x132/lph9157.h"
#elif defined (_SSD1286A)
#include "gc176x132/ssd1286a.h"
#elif defined (_HX8340)
#include "gc220x176/hx8340.h"
#elif defined (_ILI9320)
#include "gc320x240/ili9320.h"
#elif defined (_ILI9341)
#include "gc320x240/ili9341.h"
#elif defined (_S6D0139)
#include "gc320x240/s6d0139.h"
#elif defined (_SPFD5408)
#include "gc320x240/spfd5408.h"
#elif defined (_MC2PA8201)
#include "gc320x240/mc2pa8201.h"
#elif defined (_ILI9327)
#include "gc400x240/ili9327.h"
#elif defined (_ST7793)
#include "gc400x240/st7793.h"
#elif defined (_ILI9481)
#include "gc480x320/ili9481.h"
#elif defined (_R61581)
#include "gc480x320/r61581.h"
#else
#error "Unsupported display driver"
#endif

#if defined(_KS0108)
#define DISPLAY_IRQ ks0108IRQ
#elif defined(_ST7920)
#define DISPLAY_IRQ st7920IRQ
#else
#define DISPLAY_IRQ dispdrvBusIRQ
#endif

// Canvas variants
void gc160x128Init(GlcdDriver *driver);
void gc176x132Init(GlcdDriver *driver);
void gc220x176Init(GlcdDriver *driver);
void gc320x240Init(GlcdDriver *driver);
void gc400x240Init(GlcdDriver *driver);
void gc480x320Init(GlcdDriver *driver);
void gm128x64Init(GlcdDriver *driver);

void dispdrvInit(GlcdDriver **glcd);
void dispdrvPwm(void);
void dispdrvSetBrightness(uint8_t value);
uint8_t dispdrvGetBus(void);

void dispdrvBusIRQ(void);

void dispdrvWaitOperation(void);
void dispdrvSendData8(uint8_t data);
void dispdrvSendData16(uint16_t data);
void dispdrvSendFill(uint32_t size, uint16_t color);
void dispdrvSendImage(tImage *img, uint16_t w, uint16_t h);

#endif // DISPDRV_H