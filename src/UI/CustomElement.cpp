#include "CustomElement.h"

CustomElement::CustomElement(ElementContainer* parent, uint width, uint height) : Element(parent), width(width), height(height){ }

uint CustomElement::getWidth(){
	return width;
}

uint CustomElement::getHeight(){
	return height;
}

void CustomElement::setWidth(uint width){
	CustomElement::width = width;
}

void CustomElement::setHeight(uint height){
	CustomElement::height = height;
}