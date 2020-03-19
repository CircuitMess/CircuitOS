#include "Layout.h"

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

uint Layout::getAvailableWidth() const{
	return width - 2 * padding;
}

uint Layout::getAvailableHeight() const{
	return height - 2 * padding;
}

uint Layout::getWidth() const{
	return width;
}

uint Layout::getHeight() const{
	return height;
}
