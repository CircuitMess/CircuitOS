#ifndef SWTEST_DISPLAY_H
#define SWTEST_DISPLAY_H


#include <TFT_eSPI.h>
#include "Sprite.h"

class Display {
public:
	Display(uint8_t width, uint8_t height);

	void commit();
	void clear(uint32_t color);

	const TFT_eSPI& getTft() const;
	Sprite& getBaseSprite();

private:
	TFT_eSPI tft;
	Sprite baseSprite;
};


#endif //SWTEST_DISPLAY_H
