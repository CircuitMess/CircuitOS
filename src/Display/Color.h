#ifndef CIRCUITOS_COLOR_H
#define CIRCUITOS_COLOR_H

#include <Arduino.h>

typedef uint16_t Color;

struct Pixel { uint8_t r, g, b; };

Color C_RGB(uint8_t r, uint8_t g, uint8_t b);

Color C_HEX(uint32_t hex);

#endif //CIRCUITOS_COLOR_H
