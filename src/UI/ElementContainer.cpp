#include "ElementContainer.h"

ElementContainer& ElementContainer::addChild(Element* element){
	children.push_back(element);
	return *this;
}

Element* ElementContainer::getChild(int i) const{
	return children[i];
}