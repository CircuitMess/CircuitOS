#include "ElementContainer.h"
#include "../Util/Debug.h"

ElementContainer& ElementContainer::addChild(Element* element){
	children.push_back(element);
	return *this;
}

Element* ElementContainer::getChild(int i) const{
	return children[i];
}

void ElementContainer::repos(){
	for(Element* element : children){
		element->setPos(0, 0);
		element->repos();
	}
}

void ElementContainer::draw(){
	logln("Drawing container layout");

	for(Element* el : children){
		el->draw();
	}

	Element::draw();
}

Vector<Element*>& ElementContainer::getChildren(){
	return children;
}
