#include "Layout.h"
#include "../Util/Debug.h"

void Layout::reflow(){
	if(wType == CHILDREN){
		uint width = 0;

		for(Element* child : children){
			width = max(width, child->getWidth());
		}

		setWidth(width);
	}else if(wType == PARENT){
		setWidth(getParent()->getAvailableWidth());
	}

	if(hType == CHILDREN){
		uint height = 0;

		for(Element* child : children){
			height = max(height, child->getHeight());
		}

		setHeight(height);
	}else if(hType == PARENT){
		setHeight(getParent()->getAvailableWidth());
	}

	logln("Reflowing layout [" + String(getWidth()) + ", " + String(getHeight()) + "]");
	logln("W/H Type " + String(wType) + ", " + String(hType) + " [ FIXED, CHILDREN, PARENT ]");
}

void Layout::repos(){
	reposChildren();

	for(Element* element : children){
		element->repos();
	}
}

void Layout::reposChildren(){

}

void Layout::draw(){
	logln("Drawing layout");

	if(strictPos){
		reposChildren();
	}

	ElementContainer::draw();
}

Layout& Layout::setPadding(uint padding){
	Layout::padding = padding;
	return *this;
}

Layout& Layout::setGutter(uint gutter){
	Layout::gutter = gutter;
	return *this;
}

void Layout::setWidth(uint width){
	Layout::width = width;
}

void Layout::setHeight(uint height){
	Layout::height = height;
}

WHType Layout::getHType() const{
	return hType;
}

WHType Layout::getWType() const{
	return wType;
}

void Layout::setWHType(WHType wType, WHType hType){
	setWType(wType);
	setHType(hType);
}

void Layout::setWType(WHType wType){
	Layout::wType = wType;
}

void Layout::setHType(WHType hType){
	Layout::hType = hType;
}

uint Layout::getAvailableWidth(){
	return width - 2 * padding;
}

uint Layout::getAvailableHeight(){
	return height - 2 * padding;
}

uint Layout::getWidth(){
	return width;
}

uint Layout::getHeight(){
	return height;
}

uint Layout::getGutter() const{
	return gutter;
}

uint Layout::getPadding() const{
	return padding;
}

void Layout::setStrictPos(bool strictPos){
	this->strictPos = strictPos;
}
