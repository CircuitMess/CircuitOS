#include <Arduino.h>
#include "src/UI/Image.h"
#include "src/UI/Screen.h"
#include "src/CircuitOS.h"
#include "src/Util/Vector.h"
#include "src/UI/LinearLayout.h"

const byte call_icon[] PROGMEM = { 24,22,
   B00011100,B00000000,B00000000,
   B00111110,B00000000,B00000000,
   B01111111,B00000000,B00000000,
   B11111111,B10000000,B00000000,
   B11111111,B10000000,B00000000,
   B11111111,B00000000,B00000000,
   B11111110,B00000000,B00000000,
   B11111110,B00000000,B00000000,
   B11111110,B00000000,B00000000,
   B01111111,B00000000,B00000000,
   B01111111,B10000000,B00000000,
   B00111111,B11000000,B00000000,
   B00011111,B11100000,B00000000,
   B00001111,B11110000,B01100000,
   B00000111,B11111000,B11110000,
   B00000011,B11111111,B11111000,
   B00000001,B11111111,B11111100,
   B00000000,B11111111,B11111100,
   B00000000,B01111111,B11111100,
   B00000000,B00111111,B11111000,
   B00000000,B00011111,B11110000,
   B00000000,B00000111,B11100000,
};


Display display(160, 128);
Screen mainScreen(display);
LinearLayout layout(&mainScreen, VERTICAL);

Image image1(&layout, 24, 22);
Image image2(&layout, 24, 22);
unsigned i = 0;

void setup(){
	Serial.begin(115200);

	display.clear(TFT_GREEN);

	image1.sprite->clear(TFT_GREEN);
	image2.sprite->clear(TFT_GREEN);

	mainScreen.addChild(&layout);
	layout.addChild(&image1);
	layout.addChild(&image2);
	layout.addChild(&image2);
	layout.setPadding(10);
	layout.setGutter(15);
	layout.reflow();

	layout.setBorder(10, TFT_RED);

	mainScreen.draw();

	display.commit();
}

void loop(){
	// push child sprite to parent sprite

	//display.commit();

	delay(5);
	if(i++ >= 60) i = 0;
}

