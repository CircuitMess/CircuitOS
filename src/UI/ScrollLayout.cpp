#include "ScrollLayout.h"
#include "../Util/Debug.h"

ScrollLayout::ScrollLayout(ElementContainer* parent) : Layout(parent){

}

ElementContainer& ScrollLayout::addChild(Element* element){
	if(children.empty()){
		children.push_back(element);
	}else{
		children[0] = element;
	}
}

void ScrollLayout::setScroll(uint scrollX, uint scrollY){
	ScrollLayout::scrollX = scrollX;
	ScrollLayout::scrollY = scrollY;

	if(children.empty()) return;

	children[0]->setPos(padding - scrollX, padding - scrollY);
}

uint ScrollLayout::getMaxScrollX(){
	if(children.empty()) return 0;

	// child element is visible on the x axis - no scroll
	if(children[0]->getWidth() < getWidth()){
		return 0;
	}

	return children[0]->getWidth() - getWidth();
}

uint ScrollLayout::getMaxScrollY(){
	if(children.empty()) return 0;

	// child element is visible on the y axis - no scroll
	if(children[0]->getHeight() < getHeight()){
		return 0;
	}

	return children[0]->getHeight() - getHeight();
}

void ScrollLayout::reflow(){
	if(wType == CHILDREN && !children.empty()){
		setWidth(children[0]->getWidth() + 2 * padding);
	}else if(wType == PARENT){
		setWidth(getParent()->getAvailableWidth());
	}

	if(hType == CHILDREN && !children.empty()){
		setHeight(children[0]->getHeight() + 2 * padding);
	}else if(hType == PARENT){
		setHeight(getParent()->getAvailableHeight());
	}

	// resize(width, height); -- caching

	logln("Reflowing scroll layout [" + String(getWidth()) + ", " + String(getHeight()) + "]");
	logln("W/H Type " + String(wType) + ", " + String(hType) + " [ FIXED, CHILDREN, PARENT ]");
}

void ScrollLayout::draw(){
	logln("Drawing scroll layout");

	if(!children.empty()){
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