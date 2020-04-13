#ifndef SWTEST_DISPLAY_H
#define SWTEST_DISPLAY_H


#include <TFT_eSPI.h>
#include "Sprite.h"

class Sprite;

class Display {
public:
	Display(uint8_t width, uint8_t height, int8_t blPin = -1);
	Display(uint8_t width, uint8_t height, int8_t blPin, uint8_t rotation);

	void commit();
	void clear(uint32_t color);

	TFT_eSPI* getTft();
	Sprite* getBaseSprite();

	void setPower(bool power);

	uint getWidth() const;

	uint getHeight() const;

private:
	uint8_t blPin;
	uint width;
	uint height;

	TFT_eSPI tft;
	Sprite* baseSprite;
};


#endif //SWTEST_DISPLAY_H
