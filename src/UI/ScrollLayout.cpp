#include "ScrollLayout.h"
#include "../Util/Debug.h"

ScrollLayout::ScrollLayout(ElementContainer* parent) : Layout(parent){
	children.resize(1);
	children[0] = nullptr;
}

ElementContainer& ScrollLayout::addChild(Element* element){
	children[0] = element;
}

void ScrollLayout::setScroll(uint scrollX, uint scrollY){
	ScrollLayout::scrollX = scrollX;
	ScrollLayout::scrollY = scrollY;

	if(children[0] == nullptr) return;

	children[0]->setPos(padding - scrollX, padding - scrollY);
}

uint ScrollLayout::getMaxScrollX(){
	if(children[0] == nullptr) return 0;

	// child element is visible on the x axis - no scroll
	if(children[0]->getWidth() < getWidth()){
		return 0;
	}

	return children[0]->getWidth() - getWidth();
}

uint ScrollLayout::getMaxScrollY(){
	if(children[0] == nullptr) return 0;

	// child element is visible on the y axis - no scroll
	if(children[0]->getHeight() < getHeight()){
		return 0;
	}

	return children[0]->getHeight() - getHeight();
}

void ScrollLayout::reflow(){
	if(wType == CHILDREN && children[0] != nullptr){
		setWidth(children[0]->getWidth() + 2 * padding);
	}else if(wType == PARENT){
		setWidth(getParent()->getAvailableWidth());
	}

	if(hType == CHILDREN && children[0] != nullptr){
		setHeight(children[0]->getHeight() + 2 * padding);
	}else if(hType == PARENT){
		setHeight(getParent()->getAvailableHeight());
	}

	// resize(width, height); -- caching

	logln("Reflowing scroll layout [" + String(width) + ", " + String(height) + "]");
	logln("W/H Type " + String(wType) + ", " + String(hType) + " [ FIXED, CHILDREN, PARENT ]");
}

void ScrollLayout::draw(){
	logln("Drawing scroll layout");

	if(children[0] != nullptr){
		children[0]->setPos(padding - scrollX, padding - scrollY);
		children[0]->draw();
	}

	Element::draw();
}

uint ScrollLayout::getScrollX() const{
	return scrollX;
}

uint ScrollLayout::getScrollY() const{
	return scrollY;
}