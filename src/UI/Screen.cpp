#include "Screen.h"

Screen::Screen(Display& display) : ElementContainer(display.getBaseSprite()), display(&display){
	sprite->resize(display.getWidth(), display.getHeight());
	sprite->setPos(0, 0);
	sprite->clear(TFT_BLACK);
	children.resize(1);
}

Screen& Screen::addChild(Element* element){
	children[0] = element;
}

void Screen::draw(){
	Serial.println("Drawing screen");

	sprite->clear(TFT_BLACK);
	children[0]->draw();
	Element::draw();
	sprite->push();
	display->commit();
}

void Screen::pushReverse(){
	Serial.println("Reverse pushing screen");

	Element::draw();
	sprite->push();
	display->commit();
}

uint Screen::getAvailableWidth() const{
	return display->getWidth();
}

uint Screen::getAvailableHeight() const{
	return display->getHeight();
}

uint Screen::getWidth() const{
	return sprite->width();
}

uint Screen::getHeight() const{
	return sprite->height();
}
