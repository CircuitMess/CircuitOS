#include "Screen.h"
#include "../Util/Debug.h"

Screen::Screen(Display& display) : display(&display), sprite(display.getBaseSprite(), display.getWidth(), display.getHeight()){
	sprite.resize(display.getWidth(), display.getHeight());
	sprite.setPos(0, 0);
	sprite.clear(TFT_BLACK);
	children.resize(1);
	children[0] = nullptr;
}

Screen& Screen::addChild(Element* element){
	children[0] = element;
}

void Screen::draw(){
	logln("Drawing screen");

	sprite.clear(TFT_BLACK);

	ElementContainer::draw();
}

void Screen::commit(){
	sprite.push();
	display->commit();
}

uint Screen::getAvailableWidth(){
	return sprite.width();
}

uint Screen::getAvailableHeight(){
	return sprite.height();
}

uint Screen::getWidth(){
	return sprite.width();
}

uint Screen::getHeight(){
	return sprite.height();
}

Display* Screen::getDisplay() const{
	return display;
}

Sprite* Screen::getSprite(){
	return &sprite;
}

uint Screen::getX() const{
	return sprite.getX();
}

uint Screen::getY() const{
	return sprite.getY();
}

uint Screen::getTotalX() const{
	return 0;
}

uint Screen::getTotalY() const{
	return 0;
}

void Screen::setPos(uint x, uint y){
	sprite.setPos(x, y);
}
