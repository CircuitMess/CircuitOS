#include "Screen.h"
#include "../Util/Debug.h"

Screen::Screen(Display& display) : display(&display), SpriteElement(display.getBaseSprite(), display.getWidth(), display.getHeight()){
	sprite.setPos(0, 0);
	sprite.clear(TFT_BLACK);
}

Screen& Screen::addChild(Element* element){
	if(children.empty()){
		children.push_back(element);
	}else{
		children[0] = element;
	}
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

Sprite* Screen::getSprite(){
	return SpriteElement::getSprite();
}
