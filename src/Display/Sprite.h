#ifndef SWTEST_SPRITE_H
#define SWTEST_SPRITE_H


#include <TFT_eSPI.h>
#include "Display.h"

class Display;

class Sprite : public TFT_eSprite {
public:
	Sprite(TFT_eSPI* spi, uint8_t width, uint8_t height);
	Sprite(Display& display, uint8_t width, uint8_t height);
	Sprite(Sprite* sprite, uint8_t width, uint8_t height);
	Sprite& push();
	Sprite& clear(uint32_t color);
	Sprite& setPos(uint16_t x, uint16_t y);
	Sprite& resize(uint width, uint height);

	Sprite& setTransparent(bool transparent);
	Sprite& setChroma(uint32_t color);

	void pushData(uint width, uint height, uint16_t* data);

	void cleanup();

private:
	Sprite* parent;
	TFT_eSPI* parentSPI = nullptr;
	uint16_t x = 0, y = 0;

	bool chroma = false;
	uint32_t chromaKey;

	void pushImage(int32_t x, int32_t y, int32_t w, int32_t h, uint16_t *data, uint32_t chroma);

	/**
	 * Hide TFT_eSprite functions
	 */
	using TFT_eSprite::createSprite;
	using TFT_eSprite::deleteSprite;
	using TFT_eSprite::fillScreen;
	using TFT_eSprite::fillSprite;
	using TFT_eSprite::pushRotated;
	using TFT_eSprite::pushRotatedHP;
	using TFT_eSprite::pushImage;
	using TFT_eSprite::setSwapBytes;
	using TFT_eSprite::getSwapBytes;
	using TFT_eSprite::pushSprite;

};


#endif //SWTEST_SPRITE_H
