#include "ElementContainer.h"
#include "../Util/Debug.h"

ElementContainer& ElementContainer::addChild(Element* element){
	children.push_back(element);
	return *this;
}

Element* ElementContainer::getChild(int i) const{
	return children[i];
}

void ElementContainer::draw(){
	logln("Drawing ElementContainer layout");

	for(Element* el : children){
		el->draw();
	}

	Element::draw();
}
