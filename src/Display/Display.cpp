#include "Display.h"

Display::Display(uint8_t width, uint8_t height, int8_t blPin, int8_t rotation) : tft(), width(width), height(height), blPin(blPin), baseSprite(new Sprite(&tft, width, height)), rotation(rotation){

	
}
void Display::begin()
{
	if(blPin != -1)
	{
		ledcSetup(0, 2000, 8);
		//ledcAttachPin(blPin, 0);
		pinMode(blPin, OUTPUT);
		digitalWrite(blPin, HIGH);
	}

	tft.init();
	tft.invertDisplay(0);
	if(rotation != 1){
		tft.setRotation(rotation);
	}
	tft.fillScreen(TFT_PURPLE);
	baseSprite->clear(TFT_GREEN);
}
void Display::setPower(bool power){
	if(blPin != -1){
		digitalWrite(blPin, power ? HIGH : LOW);
	}
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
