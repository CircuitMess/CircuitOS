#include "ElementContainer.h"
#include "Element.h"
#include "../Util/Debug.h"

Element::Element(){
	this->parent = nullptr;
}

Element::Element(ElementContainer* parent){
	this->parent = parent;
}

Element::~Element(){

}

ElementContainer* Element::getParent(){
	return parent;
}

void Element::setBorder(uint width, Color color){
	setBorderWidth(width);
	setBorderColor(color);
}

void Element::setBorderColor(Color borderColor){
	Element::borderColor = borderColor;
}

void Element::setBorderWidth(uint borderWidth){
	Element::borderWidth = borderWidth;
}

void Element::repos(){

}

void Element::draw(){
	logr("Drawing element: ");

	if(borderWidth){
		logr("border ");

		for(int i = 0; i < borderWidth; i++){
			getParent()->getSprite()->drawRect(getTotalX() + i, getTotalY() + i, getWidth() - 2*i, getHeight() - 2*i, borderColor);
		}
	}

	logln();

	// TODO: overflow: draw over padding or erase?
}

int Element::getX() const{
	return x;
}

int Element::getY() const{
	return y;
}

int Element::getTotalX() const{
	return x + parent->getTotalX();
}

int Element::getTotalY() const{
	return y + parent->getTotalY();
}

Sprite* Element::getSprite(){
	return parent->getSprite();
}

void Element::setX(int x){
	Element::x = x;
}

void Element::setY(int y){
	Element::y = y;
}

void Element::setPos(int x, int y){
	setX(x);
	setY(y);
}

void Element::clear(){
	getSprite()->fillRect(getTotalX(), getTotalY(), getWidth(), getHeight(), TFT_BLACK);
}

void Element::setParent(ElementContainer* parent){
	Element::parent = parent;
}
