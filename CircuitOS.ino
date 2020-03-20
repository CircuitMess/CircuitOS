#include <Arduino.h>
#include "src/UI/Image.h"
#include "src/UI/Screen.h"
#include "src/CircuitOS.h"
#include "src/Util/Vector.h"
#include "src/UI/LinearLayout.h"
#include "src/UI/GridLayout.h"
#include "src/UI/ScrollLayout.h"

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
ScrollLayout scroll(&mainScreen);
LinearLayout layout(&scroll, HORIZONTAL);
GridLayout grid(&layout, 2);

Image image0(&layout, 28, 33);
Image image1(&grid, 24, 12);
Image image2(&grid, 36, 20);

void setup(){
	Serial.begin(115200);

	display.clear(TFT_GREEN);

	image0.sprite->clear(TFT_GREEN);
	image1.sprite->clear(TFT_GREEN);
	image2.sprite->clear(TFT_GREEN);

	scroll.setWHType(PARENT, CHILDREN);
	scroll.setBorder(1, TFT_RED);

	layout.setWHType(CHILDREN, CHILDREN);
	layout.setBorder(1, TFT_RED);
	layout.setPadding(5);
	layout.setGutter(5);

	grid.setWHType(CHILDREN, CHILDREN);
	grid.setBorder(1, TFT_RED);
	grid.setPadding(5);
	grid.setGutter(2);


	grid.addChild(&image1);
	grid.addChild(&image2);
	grid.addChild(&image2);
	grid.addChild(&image1);
	grid.reflow();

	layout.addChild(&image0);
	layout.addChild(&grid);
	layout.addChild(&image0);
	layout.addChild(&grid);
	layout.addChild(&image0);
	layout.reflow();

	scroll.addChild(&layout);
	scroll.reflow();

	mainScreen.addChild(&scroll);
	mainScreen.draw();
}

unsigned i = 0;
bool direction = false;

void loop(){
	scroll.setScroll(i, 0);
	layout.pushReverse();

	i += pow(-1, direction);
	delay(20);
	if(i > scroll.getMaxScrollX() || i == 0) direction = !direction;
}

