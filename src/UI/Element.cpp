#include "ElementContainer.h"
#include "Element.h"
#include "../Util/Debug.h"


Element::Element(Sprite* parent){
	sprite = new Sprite(parent, 0, 0);
}

Element::Element(ElementContainer* parent){
	sprite = new Sprite(parent->sprite, 0, 0);
	this->parent = parent;
}

void Element::resize(uint width, uint height){
	sprite->resize(width, height);
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
			sprite->drawRect(0 + i, 0 + i, getWidth() - 2*i, getHeight() - 2*i, borderColor);
		}
	}

	logln();
}

void Element::pushReverse(){
	Element::draw();
	sprite->push();
	getParent()->pushReverse();
}