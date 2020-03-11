#include "Display.h"

Display::Display(uint8_t width, uint8_t height) : tft(), baseSprite(new Sprite(&tft, width, height)){
	ledcSetup(0, 2000, 8);
	ledcAttachPin(21, 0);

	tft.init();
	tft.invertDisplay(0);
	tft.setRotation(3);
	tft.fillScreen(TFT_PURPLE);

	baseSprite->clear(TFT_GREEN);
}

void Display::commit(){
	baseSprite->push();
}

void Display::clear(uint32_t color){
	baseSprite->clear(color);
}

const TFT_eSPI& Display::getTft() const{
	return tft;
}

Sprite* Display::getBaseSprite(){
	return baseSprite;
}
