#include "ElementContainer.h"

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
