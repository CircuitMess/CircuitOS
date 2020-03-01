#ifndef SWTEST_SPRITE_H
#define SWTEST_SPRITE_H


#include <TFT_eSPI.h>
#include "Display.h"

class Sprite : private TFT_eSprite {
public:
	Sprite(Display& display, uint8_t width, uint8_t height);
	Sprite(Sprite* sprite, uint8_t width, uint8_t height);
	Sprite& push();
	Sprite& clear(uint32_t color);
	Sprite& setPos(uint16_t x, uint16_t y);
private:
	TFT_eSprite* parent;
	uint16_t x, y;
};


#endif //SWTEST_SPRITE_H
