#ifndef CIRCUITOS_COLOR_H
#define CIRCUITOS_COLOR_H

#include <Arduino.h>

typedef uint16_t Color;

Color C_RGB(uint8_t r, uint8_t g, uint8_t b);

Color C_HEX(uint32_t hex);

struct HSV{
	uint8_t h; //Hue (0-180)
	float s; //Saturation (0-1.0)
	float v; //Value (0-1.0)
};

uint32_t HSVtoRGB888(HSV hsv);
Color HSVtoRGB565(HSV hsv);

#endif //CIRCUITOS_COLOR_H
