#include "ElementContainer.h"

ElementContainer& ElementContainer::addChild(Element* element){
	children.push_back(element);
	return *this;
}

