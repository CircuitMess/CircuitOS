#include "Display.h"

Display::Display(uint8_t width, uint8_t height) : tft(), baseSprite(&tft){
	ledcSetup(0, 2000, 8);
	ledcAttachPin(21, 0);

	tft.init();
	tft.invertDisplay(0);
	tft.setRotation(3);
	tft.fillScreen(TFT_PURPLE);

	baseSprite.createSprite(168, 128);
	baseSprite.fillSprite(TFT_GREEN);
}

void Display::commit(){
	baseSprite.pushSprite(0, 0);
}

void Display::clear(uint32_t color){
	baseSprite.fillSprite(color);
}

const TFT_eSPI& Display::getTft() const{
	return tft;
}

TFT_eSprite& Display::getBaseSprite(){
	return baseSprite;
}
