#include "Color.h"

const Pixel Pixel::Red = { 255, 0, 0};
const Pixel Pixel::Green = { 0, 255, 0};
const Pixel Pixel::Blue = { 0, 0, 255};
const Pixel Pixel::Yellow = { 255, 255, 0};
const Pixel Pixel::Cyan = { 0, 255, 255};
const Pixel Pixel::Magenta = { 255, 0, 255};
const Pixel Pixel::White = { 255, 255, 255};
const Pixel Pixel::Black = { 0, 0, 0};

Color C_RGB(uint8_t r, uint8_t g, uint8_t b){
	return (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3));
}

Color C_HEX(uint32_t hex){
	return C_RGB(
			(hex >> 16) & 0xFF,
			(hex >> 8) & 0xFF,
			hex & 0xFF
	);
}