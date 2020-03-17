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
