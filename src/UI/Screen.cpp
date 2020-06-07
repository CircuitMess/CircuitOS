#include "Screen.h"
#include "../Util/Debug.h"

Screen::Screen(Display& display) : Screen(display, display.getWidth(), display.getHeight()){

}

Screen::Screen(Display& display, uint width, uint height) : display(&display), SpriteElement(display.getBaseSprite(), width, height){
	sprite.setPos(0, 0);
	sprite.clear(TFT_BLACK);
}

Screen& Screen::addChild(Element* element){
	if(element == nullptr){
		children.clear();
	}else if(children.empty()){
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
	return getWidth();
}

uint Screen::getAvailableHeight(){
	return getHeight();
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

int Screen::getX() const{
	return sprite.getX();
}

int Screen::getY() const{
	return sprite.getY();
}

int Screen::getTotalX() const{
	return 0; // getX();
}

int Screen::getTotalY() const{
	return 0; // getY();
}

void Screen::setPos(int x, int y){
	sprite.setPos(x, y);
}

Sprite* Screen::getSprite(){
	return SpriteElement::getSprite();
}
