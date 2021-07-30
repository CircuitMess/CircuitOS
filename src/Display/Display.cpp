#include "Display.h"

Display::Display(uint16_t width, uint16_t height, int8_t blPin, int8_t rotation, bool mirror) : tft(), blPin(blPin),
		width(width), height(height), baseSprite(new Sprite(&tft, width, height)), rotation(rotation), mirror(mirror){

	if(baseSprite == nullptr){
		Serial.println("Base sprite init error");
	}
}

void Display::begin()
{
	if(blPin != -1)
	{
		//ledcSetup(0, 2000, 8);
		//ledcAttachPin(blPin, 0);
		pinMode(blPin, OUTPUT);
		digitalWrite(blPin, HIGH);
	}

#ifndef CIRCUITOS_LOVYANGFX
	tft.setAttribute(PSRAM_ENABLE, false);
#endif
	tft.init();
	tft.setRotation(3);
	tft.setColorDepth(16);
#ifndef CIRCUITOS_LOVYANGFX
	tft.setAttribute(PSRAM_ENABLE, false);
#endif

	tft.writecommand(17); //wakeup command in case display driver is in sleep mode

	tft.invertDisplay(0);
	if(rotation != 1){
		tft.setRotation(rotation);
	}
	tft.fillScreen(TFT_BLACK);
	baseSprite->clear(TFT_BLACK);
	static_cast<TFT_eSprite*>(baseSprite)->setSwapBytes(false);

	if(mirror){
		mirrorBuffer = static_cast<uint16_t*>(malloc(sizeof(uint16_t) * getWidth() * getHeight()));
	}
}
void Display::setPower(bool power){
	if(blPin != -1){
		digitalWrite(blPin, power ? HIGH : LOW);
	}
}

void Display::commit(){
	if(mirror){
		for(int i = 0; i < getWidth(); i++){
			for(int j = 0; j < getHeight(); j++){
				mirrorBuffer[j * getWidth() + i] = baseSprite->readPixel(getWidth() - i - 1, j);
			}
		}

		baseSprite->drawIcon(mirrorBuffer, 0, 0, getWidth(), getHeight());
	}
#ifdef CIRCUITOS_LOVYANGFX
	baseSprite->pushRotateZoom(161, 121, 0, 2, 2);
#else
	baseSprite->push();
#endif
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
