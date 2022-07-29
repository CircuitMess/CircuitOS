#ifndef CIRCUITOS_COLOR_H
#define CIRCUITOS_COLOR_H

#include <Arduino.h>

typedef uint16_t Color;

struct Pixel { uint8_t r, g, b;
	static const Pixel Red;
	static const Pixel Green;
	static const Pixel Blue;
	static const Pixel Magenta;
	static const Pixel Cyan;
	static const Pixel Yellow;
	static const Pixel White;
	static const Pixel Black;
};

Color C_RGB(uint8_t r, uint8_t g, uint8_t b);

Color C_HEX(uint32_t hex);

#endif //CIRCUITOS_COLOR_H
