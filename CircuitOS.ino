#include <Arduino.h>
#include "src/UI/Image.h"
#include "src/UI/Screen.h"
#include "src/CircuitOS.h"
#include "src/Util/Vector.h"
#include "src/UI/LinearLayout.h"
#include "src/UI/GridLayout.h"
#include "src/UI/ScrollLayout.h"
#include "src/Input/Input.h"
#include "src/Bitmaps/Bitmaps.hpp"
#include "src/Input/InputGPIO.h"
#include "src/Update/UpdateManager.h"

#define BTN_A 32
#define BTN_B 34
#define BTN_C 39
#define BTN_D 36

Display display(128, 128, 18, 4);
Screen mainScreen(display);
LinearLayout screenLayout(&mainScreen, HORIZONTAL);
LinearLayout btnLayout(&screenLayout, VERTICAL);
Image imageR(&btnLayout, 18, 18);
Image imageL(&btnLayout, 18, 18);
Image imageY(&btnLayout, 18, 18);
Image imageN(&btnLayout, 18, 18);
ScrollLayout mainScroll(&screenLayout);
GridLayout grid(&mainScroll, 2);

#define ELEMENTS 7
uint selected = 0;
Color colors[ELEMENTS] = { TFT_GREEN, TFT_PURPLE, TFT_WHITE, TFT_YELLOW, TFT_BLUE, TFT_LIGHTGREY, TFT_OLIVE };

Vector<Image*> gridImages;

Input* input = nullptr;

void setUI();
void scroll();
void selectElement(uint element);

void btnRPress(){
	selectElement((selected + 1) % ELEMENTS);
}

void btnLPress(){
	if(selected == 0){
		selectElement(ELEMENTS - 1);
	}else{
		selectElement(selected - 1);
	}
}


void setup(){
	Serial.begin(115200);
	input = new InputGPIO();

	setUI();
	mainScreen.draw();
	mainScreen.commit();

	input->setBtnReleaseCallback(BTN_A, btnRPress);
	input->setBtnPressCallback(BTN_B, btnLPress);

	UpdateManager::addListener(input);
}

void loop(){
	UpdateManager::update();
}

void selectElement(uint element){
	gridImages[selected]->setBorderWidth(0);
	gridImages[selected]->draw();

	gridImages[element]->setBorderWidth(3);
	gridImages[element]->draw();

	selected = element;
	scroll();
	mainScreen.commit();
}

void scroll(){
	Image* gridImage = gridImages[selected];

	uint elStart = grid.getPadding() + (selected/2) * (gridImage->getHeight() + grid.getGutter());
	uint elEnd = elStart + gridImage->getHeight();

	uint screenStart = mainScroll.getScrollY();
	uint screenEnd = screenStart + display.getHeight();

	uint newScroll = mainScroll.getScrollY();
	Serial.println("Element end / screen stop: " + String(elEnd) + " / " + String(screenEnd));
	if(elStart < screenStart){
		newScroll = elStart;

		if(newScroll == grid.getPadding()){
			newScroll = 0;
		}else{
			newScroll -= grid.getGutter() / 2;
		}
	}else if(elEnd > screenEnd){
		newScroll += elEnd - screenEnd;

		Serial.println("A / B: " + String(newScroll + display.getHeight()) + " / " + String(grid.getHeight() - grid.getPadding()));
		if(newScroll + display.getHeight() == grid.getHeight() - grid.getPadding()){
			newScroll += grid.getPadding();
		}else{
			newScroll += grid.getGutter() / 2;
		}
	}

	if(newScroll == mainScroll.getScrollY()){
		return;
	}

	if(newScroll != mainScroll.getScrollY()){
		mainScroll.setScroll(0, newScroll);

		mainScroll.clear();
		mainScroll.draw();
	}
}

void setUI(){
	display.clear(TFT_GREEN);

	/** Buttons */
	imageR.getSprite()->clear(TFT_BLACK);
	imageL.getSprite()->clear(TFT_BLACK);
	imageY.getSprite()->clear(TFT_BLACK);
	imageN.getSprite()->clear(TFT_BLACK);

	imageR.getSprite()->drawIcon(arrowRight, 0, 0, 18, 18, 1);
	imageL.getSprite()->drawIcon(arrowRight, 0, 0, 18, 18, 1);
	imageY.getSprite()->drawIcon(yes, 0, 0, 18, 18, 1);
	imageN.getSprite()->drawIcon(cross, 0, 0, 18, 18, 1);

	imageL.getSprite()->rotate(2);

	btnLayout.setWHType(FIXED, PARENT);
	btnLayout.setWidth(28);
	btnLayout.setPadding(5);
	btnLayout.setGutter(15);
	//btnLayout.setBorder(1, TFT_RED);

	btnLayout.addChild(&imageR);
	btnLayout.addChild(&imageL);
	btnLayout.addChild(&imageY);
	btnLayout.addChild(&imageN);

	/** Grid */

	for(int i = 0; i < ELEMENTS; i++){
		Image* gridImage = new Image(&grid, 35, 35);
		gridImages.push_back(gridImage);

		gridImage->getSprite()->clear(colors[i]);
		gridImage->setBorderColor(TFT_RED);
		grid.addChild(gridImage);
	}

	gridImages.front()->setBorderWidth(3);

	grid.setWHType(PARENT, CHILDREN);
	grid.setPadding(10).setGutter(10);

	/** Layout */

	mainScroll.setWHType(FIXED, PARENT);
	mainScroll.setWidth(100);
	//mainScroll.setBorder(1, TFT_RED);
	mainScroll.addChild(&grid);

	screenLayout.setWHType(PARENT, PARENT);
	screenLayout.addChild(&mainScroll).addChild(&btnLayout);

	screenLayout.reflow();
	mainScroll.reflow();
	grid.reflow();
	btnLayout.reflow();

	mainScreen.addChild(&screenLayout);
	mainScreen.repos();
}