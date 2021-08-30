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
	return *this;
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

void ScrollLayout::scrollIntoView(uint child, int over){
	if(children.empty()) return;

	ElementContainer* container = reinterpret_cast<ElementContainer*>(children[0]);
	if(child >= container->getChildren().size()) return;
	Element* childElement = container->getChild(child);

	int scrollX = this->scrollX;
	int scrollY = this->scrollY;

	if(childElement->getX() < getScrollX()){
		scrollX = (int) childElement->getX() - over;
	}else if((childElement->getX() + childElement->getWidth() + over) > (getScrollX() + getWidth())){
		scrollX = (int) childElement->getX() + childElement->getWidth() + over - getWidth();
	}

	if(childElement->getY() < getScrollY()){
		scrollY = (int) childElement->getY() - over;
	}else if((childElement->getY() + childElement->getHeight() + over) > (getScrollY() + getHeight())){
		scrollY = (int) childElement->getY() + childElement->getHeight() + over - getHeight();
	}

	setScroll(max(0, min(scrollX, (int) getMaxScrollX())), max(0, min(scrollY, (int) getMaxScrollY())));
}
