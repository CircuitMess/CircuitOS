#ifndef SWTEST_DISPLAY_H
#define SWTEST_DISPLAY_H


#include <TFT_eSPI.h>
#include "Sprite.h"

class Sprite;

class Display {
public:
	Display(uint8_t width, uint8_t height, int8_t blPin = -1, int8_t rotation = -1);
	void begin();
	void commit();
	void clear(uint32_t color);

	TFT_eSPI* getTft();
	Sprite* getBaseSprite();

	void setPower(bool power);

	uint getWidth() const;

	uint getHeight() const;

private:
	TFT_eSPI tft; 
	uint width;
	uint height;
	int8_t blPin;
	int8_t rotation;

	Sprite* baseSprite;
};


#endif //SWTEST_DISPLAY_H
