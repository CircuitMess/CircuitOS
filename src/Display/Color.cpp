#include "Color.h"

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