#include "Screen.h"
#include "../Util/Debug.h"

Screen::Screen(Display& display) : ElementContainer(display.getBaseSprite()), display(&display){
	sprite->resize(display.getWidth(), display.getHeight());
	sprite->setPos(0, 0);
	sprite->clear(TFT_BLACK);
	children.resize(1);
	children[0] = nullptr;
}

Screen& Screen::addChild(Element* element){
	children[0] = element;
}

void Screen::draw(){
	logln("Drawing screen");

	sprite->clear(TFT_BLACK);

	if(children[0] != nullptr){
		children[0]->draw();
	}

	Element::draw();
	sprite->push();
	display->commit();
}

void Screen::pushReverse(){
	logln("Reverse pushing screen");

	Element::draw();
	sprite->push();
	display->commit();
}

uint Screen::getAvailableWidth() const{
	return sprite->width();
}

uint Screen::getAvailableHeight() const{
	return sprite->height();
}

uint Screen::getWidth() const{
	return sprite->width();
}

uint Screen::getHeight() const{
	return sprite->height();
}

Display* Screen::getDisplay() const{
	return display;
}
