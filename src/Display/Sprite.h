#ifndef SWTEST_SPRITE_H
#define SWTEST_SPRITE_H


#include <TFT_eSPI.h>
#include "Display.h"
#include "Color.h"

class Display;

class Sprite : public TFT_eSprite {
public:
	Sprite(TFT_eSPI* spi, uint8_t width, uint8_t height);
	Sprite(Display& display, uint8_t width, uint8_t height);
	Sprite(Sprite* sprite, uint8_t width, uint8_t height);
	virtual ~Sprite();

	Sprite& push();
	Sprite& clear(uint32_t color);
	Sprite& setPos(int32_t x, int32_t y);
	Sprite& resize(uint width, uint height);

	int32_t getX() const;

	int32_t getY() const;

	Sprite& setTransparent(bool transparent);
	Sprite& setChroma(Color color);

	void pushData(uint width, uint height, uint16_t* data);

	void rotate(uint times);
	// void drawIcon(const unsigned short* icon, uint x, uint y, uint width, uint height, uint scale);
	void drawMonochromeIcon(const byte* icon, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t scale = 1, uint32_t color = TFT_BLACK);
	void drawIcon(const unsigned short* icon, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t scale = 1, int32_t maskingColor = -1);
	void printCenter(const char* text);
	void printCenter(String text);
	void printCenter(uint32_t text);
	void printCenter(int text);
	void printCenter(float text);

	void cleanup();

	bool created();

	void setParent(Sprite* parent);

	Sprite* getParent() const;

private:
	Sprite* parent;
	TFT_eSPI* parentSPI = nullptr;
	int32_t x = 0, y = 0;

	bool chroma = false;
	Color chromaKey = TFT_TRANSPARENT;

	void pushImage(int32_t x, int32_t y, int32_t w, int32_t h, uint16_t *data, uint32_t chroma);

	/**
	 * Hide TFT_eSprite functions
	 */
	using TFT_eSprite::createSprite;
	using TFT_eSprite::deleteSprite;
	using TFT_eSprite::fillScreen;
	using TFT_eSprite::fillSprite;
	using TFT_eSprite::pushRotated;
	using TFT_eSprite::pushImage;
	using TFT_eSprite::setSwapBytes;
	using TFT_eSprite::getSwapBytes;
	using TFT_eSprite::pushSprite;

};


#endif //SWTEST_SPRITE_H
