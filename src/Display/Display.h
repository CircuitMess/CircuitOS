#ifndef SWTEST_DISPLAY_H
#define SWTEST_DISPLAY_H


#include <TFT_eSPI.h>
#include "Sprite.h"

class Sprite;

class Display {
public:

	/**
	 *
	 * @param width
	 * @param height
	 * @param blPin
	 * @param rotation
	 * @param mirror Horizontal display mirroring. WARNING: decimates the framerate and uses width*height*2 bytes of RAM
	 */
	Display(uint8_t width, uint8_t height, int8_t blPin = -1, int8_t rotation = -1, bool mirror = false);
	void begin();
	void commit();
	void clear(uint32_t color);

	TFT_eSPI* getTft();
	Sprite* getBaseSprite();

	/**
	 * Sets the backlight power.
	 * @param power
	 */
	void setPower(bool power);

	uint getWidth() const;

	uint getHeight() const;

private:
	TFT_eSPI tft; 
	uint width;
	uint height;
	int8_t blPin;
	int8_t rotation;

	uint16_t* mirrorBuffer = nullptr;
	bool mirror;

	Sprite* baseSprite;
};


#endif //SWTEST_DISPLAY_H
