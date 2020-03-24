#include "ElementContainer.h"
#include "Element.h"
#include "../Util/Debug.h"

Element::Element(){
	this->parent = nullptr;
}

Element::Element(ElementContainer* parent){
	this->parent = parent;
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

void Element::draw(){
	logr("Drawing element: ");

	if(borderWidth){
		logr("border ");

		for(int i = 0; i < borderWidth; i++){
			getParent()->getSprite()->drawRect(getTotalX() + i, getTotalY() + i, getWidth() - 2*i, getHeight() - 2*i, borderColor);
		}
	}

	logln();
}

uint Element::getX() const{
	return x;
}

uint Element::getY() const{
	return y;
}

uint Element::getTotalX() const{
	return x + parent->getTotalX();
}

uint Element::getTotalY() const{
	return y + parent->getTotalY();
}

Sprite* Element::getSprite(){
	return parent->getSprite();
}

void Element::setX(uint x){
	Element::x = x;
}

void Element::setY(uint y){
	Element::y = y;
}

void Element::setPos(uint x, uint y){
	setX(x);
	setY(y);
}

void Element::clear(){
	Serial.println("Clearing element at [" + String(getTotalX()) + ", " + String(getTotalX()) + "] w/h [" + String(getWidth()) + ", " + String(getHeight()) + "]");
	getSprite()->fillRect(getTotalX(), getTotalY(), getWidth(), getHeight(), TFT_BLACK);
}
