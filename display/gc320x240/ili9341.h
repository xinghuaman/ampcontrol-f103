#ifndef ILI9341_H
#define ILI9341_H

#include <inttypes.h>

#include "../glcd.h"

void ili9341Init(GlcdDriver **driver);
void ili9341Clear(void);

void ili9341Sleep(void);
void ili9341Wakeup(void);

void ili9341DrawPixel(int16_t x, int16_t y, uint16_t color);
void ili9341DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

void ili9341DrawImage(tImage *img);

#endif // ILI9341_H