#include "LinearLayout.h"

LinearLayout::LinearLayout(ElementContainer* parent, LayoutDirection direction) : Layout(parent, 1, 1), direction(direction){
	reflow();
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
			y += gutter + el->height;
		}else if(direction == HORIZONTAL){
			x += gutter + el->width;
		}
	}

	sprite->push();
}

void LinearLayout::reflow(){
	uint width = 0;
	uint height = 0;

	if(direction == VERTICAL){
		width = getParent()->width;

		for(const Element* el : children){
			height += el->height + gutter;
		}

		height -= gutter;
		height += padding * 2;
	}else if(direction == HORIZONTAL){
		height = getParent()->height;

		for(const Element* el : children){
			width += el->width + gutter;
		}

		width -= gutter;
		width += padding * 2;
	}

	Serial.println("Reflowing linear layout [" + String(width) + ", " + String(height) + "]");

	resize(width, height);
}

uint LinearLayout::getAvailableWidth(){
	return 0;
}

uint LinearLayout::getAvailableHeight(){
	return 0;
}

