#ifndef LS020_H
#define LS020_H

#include <inttypes.h>

#include "glcd.h"

void ls020Init(GlcdDriver **driver);
void ls020Clear(void);

void ls020Sleep(void);
void ls020Wakeup(void);

void ls020DrawPixel(int16_t x, int16_t y, uint16_t color);
void ls020DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

void ls020DrawFontChar(CharParam *param);

#endif // LS020_H