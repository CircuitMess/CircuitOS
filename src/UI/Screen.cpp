#include "Screen.h"

Screen::Screen(Display& display) : ElementContainer(display.getBaseSprite(), 160, 128), display(&display){
	sprite->setPos(0, 0);
	sprite->clear(TFT_BLACK);
	children.resize(1);
}

Screen& Screen::addChild(Element& element){
	children[0] = &element;
}

void Screen::draw(){
	Serial.println("Drawing screen");
	sprite->clear(TFT_BLACK);
	children[0]->draw();
	sprite->push();
}

uint Screen::getAvailableWidth(){
	return display->getWidth();
}

uint Screen::getAvailableHeight(){
	return display->getHeight();
}
