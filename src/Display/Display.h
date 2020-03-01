#ifndef SWTEST_DISPLAY_H
#define SWTEST_DISPLAY_H


#include <TFT_eSPI.h>

class Display {
public:
	Display(uint8_t width, uint8_t height);

	void commit();
	void clear(uint32_t color);

	const TFT_eSPI& getTft() const;
	TFT_eSprite& getBaseSprite();

private:
	TFT_eSPI tft;
	TFT_eSprite baseSprite;
};


#endif //SWTEST_DISPLAY_H
