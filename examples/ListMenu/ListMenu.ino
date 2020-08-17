#include <Arduino.h>
#include <CircuitOS.h>
#include <UI/Image.h>
#include <UI/Screen.h>
#include <CircuitOS.h>
#include <Util/Vector.h>
#include <UI/LinearLayout.h>
#include <UI/GridLayout.h>
#include <UI/ScrollLayout.h>
#include <Input/InputGPIO.h>
#include <Bitmaps/Bitmaps.hpp>
#include <Elements/ListMenu.h>
#include <Loop/LoopManager.h>

#define BTN_A 32
#define BTN_B 34
#define BTN_C 39
#define BTN_D 36

Display display(128, 128, 18, 4);
Screen screen(display);
ListMenu menu(&screen, "ListMenu");

#define ELEMENTS 8

Input* input;

void setUI();
void scroll();
void selectElement(uint element);

void btnRPress(){
	menu.selectNext();
	screen.commit();
}

void btnLPress(){
	menu.selectPrev();
	screen.commit();
}


void setup(){
	Serial.begin(115200);
	input = new InputGPIO();

	setUI();
	screen.draw();
	screen.commit();

	input->setBtnReleaseCallback(BTN_A, btnRPress);
	input->setBtnPressCallback(BTN_B, btnLPress);

	LoopManager::addListener(input);
}

void loop(){
	LoopManager::loop();
}

void setUI(){
	display.clear(TFT_GREEN);

	menu.setWHType(PARENT, PARENT);
	for(int i = 0; i < ELEMENTS; i++){
		menu.addItem("Foo ");
	}
	menu.reflow();

	screen.addChild(&menu);
	screen.repos();
}