#include "ElementContainer.h"

Element::Element(Sprite* parent, uint width, uint height) : width(width), height(height){
	sprite = new Sprite(parent, width, height);
}

Element::Element(ElementContainer* parent, uint width, uint height) : width(width), height(height){
	sprite = new Sprite(parent->sprite, width, height);
	this->parent = parent;
}

void Element::resize(uint width, uint height){
	sprite->resize(width, height);
}

ElementContainer* Element::getParent(){
	return parent;
}
