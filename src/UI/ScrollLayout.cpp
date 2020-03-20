#include "ScrollLayout.h"
#include "../Util/Debug.h"

ScrollLayout::ScrollLayout(ElementContainer* parent) : Layout(parent){
	children.resize(1);
}

ElementContainer& ScrollLayout::addChild(Element* element){
	children[0] = element;
}

void ScrollLayout::setScroll(uint scrollX, uint scrollY){
	ScrollLayout::scrollX = scrollX;
	ScrollLayout::scrollY = scrollY;

	children[0]->sprite->setPos(padding - scrollX, padding - scrollY);
}

uint ScrollLayout::getMaxScrollX() const{
	// child element is visible on the x axis - no scroll
	if(children[0]->getWidth() < getWidth()){
		return 0;
	}

	return children[0]->getWidth() - getWidth();
}

uint ScrollLayout::getMaxScrollY() const{
	// child element is visible on the y axis - no scroll
	if(children[0]->getHeight() < getHeight()){
		return 0;
	}

	return children[0]->getHeight() - getHeight();
}

void ScrollLayout::reflow(){
	if(wType == CHILDREN){
		setWidth(children[0]->getWidth() + 2 * padding);
	}else if(wType == PARENT){
		setWidth(getParent()->getAvailableWidth());
	}

	if(hType == CHILDREN){
		setHeight(children[0]->getHeight() + 2 * padding);
	}else if(hType == PARENT){
		setHeight(getParent()->getAvailableHeight());
	}

	resize(width, height);

	logln("Reflowing scroll layout [" + String(width) + ", " + String(height) + "]");
	logln("W/H Type " + String(wType) + ", " + String(hType) + " [ FIXED, CHILDREN, PARENT ]");
}

void ScrollLayout::draw(){
	logln("Drawing scroll layout");

	sprite->clear(TFT_BLACK);

	children[0]->draw();

	Element::draw();
	sprite->push();
}
