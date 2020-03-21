#ifndef SWTEST_DISPLAY_H
#define SWTEST_DISPLAY_H


#include <TFT_eSPI.h>
#include "Sprite.h"

class Sprite;

class Display {
public:
	Display(uint8_t width, uint8_t height, uint8_t blPin);
	Display(uint8_t width, uint8_t height, uint8_t blPin, uint8_t rotation);

	void commit();
	void clear(uint32_t color);

	TFT_eSPI* getTft();
	Sprite* getBaseSprite();

	uint getWidth() const;

	uint getHeight() const;

private:
	TFT_eSPI tft;
	Sprite* baseSprite;
	uint8_t blPin;

	uint width;
	uint height;
};


#endif //SWTEST_DISPLAY_H
