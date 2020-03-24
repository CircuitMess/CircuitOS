#include "LayeredLayout.h"
#include "../Util/Debug.h"

void LayeredLayout::reflow(){
	setWidth(getParent()->getWidth());
	setHeight(getParent()->getHeight());

	// resize(width, height); -- caching
}

void LayeredLayout::draw(){
	logln("Drawing layered layout");

	for(Element* el : children){
		el->draw();
	}

	Element::draw();
}