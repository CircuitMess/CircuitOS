#include "ScrollLayout.h"
#include "../Util/Debug.h"

ScrollLayout::ScrollLayout(ElementContainer* parent) : Layout(parent){

}

void ScrollLayout::reposChildren(){
	logln("Repositioning scroll layout");

	if(!children.empty()){
		children[0]->setPos(padding - scrollX, padding - scrollY);
	}
}

void ScrollLayout::draw(){
	if(!strictPos){
		Layout::draw();
		return;
	}

	if(!children.empty()){
		children[0]->setPos(padding - scrollX, padding - scrollY);
		children[0]->draw();
	}

	Element::draw();
}

ElementContainer& ScrollLayout::addChild(Element* element){
	if(element == nullptr){
		children.clear();
	}else if(children.empty()){
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

uint ScrollLayout::getScrollX() const{
	return scrollX;
}

uint ScrollLayout::getScrollY() const{
	return scrollY;
}
