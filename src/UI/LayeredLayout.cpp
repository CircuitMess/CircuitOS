#include "LayeredLayout.h"
#include "../Util/Debug.h"

void LayeredLayout::reflow(){
	setWidth(getParent()->getWidth());
	setHeight(getParent()->getHeight());

	resize(width, height);
}

void LayeredLayout::draw(){
	logln("Drawing layered layout");

	sprite->clear(TFT_BLACK);

	for(Element* el : children){
		el->draw();
	}

	Element::draw();
	sprite->push();
}

void LayeredLayout::pushReverse(){
	Element::pushReverse();
}
