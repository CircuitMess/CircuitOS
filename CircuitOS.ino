#include <Arduino.h>
#include "src/UI/Image.h"
#include "src/UI/Screen.h"
#include "src/CircuitOS.h"
#include "src/Util/Vector.h"
#include "src/UI/LinearLayout.h"
#include "src/UI/GridLayout.h"
#include "src/UI/ScrollLayout.h"
#include "src/Util/Task.h"
#include "src/Input/Input.h"

#define BTN_A 32
#define BTN_B 34
#define BTN_C 39
#define BTN_D 36

void setUI();
Display display(128, 128, 18, 4);
Screen mainScreen(display);
ScrollLayout scroll(&mainScreen);
LinearLayout layout(&scroll, HORIZONTAL);
GridLayout grid(&layout, 2);
Image image0(&layout, 28, 33);
Image image1(&grid, 24, 12);
Image image2(&grid, 36, 20);
Input input;

void btnAPress(){
	Serial.println("Button A");
}

void btnBPress(){
	Serial.println("Button B");
}

void btnCPress(){
	Serial.println("Button C");
}

void btnDPress(){
	Serial.println("Button D");
}

void btnDRelease(){
	Serial.println("Button D release");
}

void setup(){
	Serial.begin(115200);

	setUI();
	mainScreen.draw();

	input.setBtnPressCallback(BTN_A, btnAPress);
	input.setBtnPressCallback(BTN_B, btnBPress);
	input.setBtnPressCallback(BTN_C, btnCPress);
	input.setBtnPressCallback(BTN_D, btnDPress);
	input.setBtnReleaseCallback(BTN_D, btnDRelease);

	input.start();
}

unsigned i = 0;
bool direction = false;

void loop(){
	scroll.sprite->setPos(0, 0);
	scroll.setScroll(i, 0);
	layout.pushReverse();

	scroll.sprite->setPos(0, 64);
	scroll.setScroll(scroll.getMaxScrollX() - i, 0);
	layout.pushReverse();

	i += pow(-1, direction);
	//delay(20);
	if(i > scroll.getMaxScrollX() || i == 0) direction = !direction;
}

void setUI(){
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
}