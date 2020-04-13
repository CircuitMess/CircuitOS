#include "Display.h"

Display::Display(uint8_t width, uint8_t height, int8_t blPin) : tft(), width(width), height(height), blPin(blPin), baseSprite(new Sprite(&tft, width, height)){

	if(blPin != -1)
	{
		ledcSetup(0, 2000, 8);
		//ledcAttachPin(blPin, 0);
		pinMode(blPin, OUTPUT);
		digitalWrite(blPin, HIGH);
	}

	tft.init();
	tft.invertDisplay(0);
	tft.setRotation(3);
	tft.fillScreen(TFT_PURPLE);

	baseSprite->clear(TFT_GREEN);
}

void Display::setPower(bool power){
	if(blPin != -1)
		digitalWrite(blPin, power ? HIGH : LOW);
}

Display::Display(uint8_t width, uint8_t height, int8_t blPin, uint8_t rotation) : Display(width, height, blPin){
	tft.setRotation(rotation);
}

void Display::commit(){
	baseSprite->push();
}

void Display::clear(uint32_t color){
	baseSprite->clear(color);
}

TFT_eSPI* Display::getTft(){
	return &tft;
}

Sprite* Display::getBaseSprite(){
	return baseSprite;
}

uint Display::getWidth() const{
	return width;
}

uint Display::getHeight() const{
	return height;
}
