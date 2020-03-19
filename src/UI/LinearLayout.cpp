#include "LinearLayout.h"

LinearLayout::LinearLayout(ElementContainer* parent, LayoutDirection direction) : Layout(parent), direction(direction){

}

void LinearLayout::draw(){
	// Vertical
	Serial.println("Drawing linear layout");

	sprite->clear(TFT_BLACK);

	int x = padding;
	int y = padding;

	for(Element* el : children){
		el->sprite->setPos(x, y);
		el->draw();

		if(direction == VERTICAL){
			y += gutter + el->getHeight();
		}else if(direction == HORIZONTAL){
			x += gutter + el->getWidth();
		}
	}

	Element::draw();

	sprite->push();
}

void LinearLayout::reflow(){
	uint width = 0;
	uint height = 0;

	// TODO WHType, current height: children, width: parent

	if(direction == VERTICAL){
		width = getParent()->getWidth();

		for(const Element* el : children){
			height += el->getHeight() + gutter;
		}

		height -= gutter;
		height += padding * 2;
	}else if(direction == HORIZONTAL){
		height = getParent()->getHeight();

		for(const Element* el : children){
			width += el->getWidth() + gutter;
		}

		width -= gutter;
		width += padding * 2;
	}

	Serial.println("Reflowing linear layout [" + String(width) + ", " + String(height) + "]");

	setWidth(width);
	setHeight(height);
	resize(width, height);
}

uint LinearLayout::getAvailableWidth(){
	return 0;
}

uint LinearLayout::getAvailableHeight(){
	return 0;
}

uint LinearLayout::getWidth() const{
	return width;
}

uint LinearLayout::getHeight() const{
	return height;
}

