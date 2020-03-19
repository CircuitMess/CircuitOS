#include "GridLayout.h"

GridLayout::GridLayout(ElementContainer* parent, uint cols) : Layout(parent), cols(cols){

}

void GridLayout::draw(){
	Serial.println("Drawing grid layout");

	sprite->clear(TFT_BLACK);

	uint x = padding;
	uint y = padding;

	uint col = 0;
	uint maxHeight = 0;
	for(Element* el : children){
		el->sprite->setPos(x, y);
		el->draw();

		x += el->getWidth() + gutter;
		maxHeight = max(maxHeight, el->getHeight());

		if(++col == cols){
			y += maxHeight + gutter;
			x = padding;
			maxHeight = 0;
			col = 0;
		}
	}

	Element::draw();

	// TODO: overflow: draw over padding or erase?

	sprite->push();
}

void GridLayout::reflow(){
	width = wType == FIXED ? width : 0;
	height = hType == FIXED ? height : 0;

	if(wType == PARENT){
		width = getParent()->getAvailableWidth();
	}else if(wType == CHILDREN){
		width += 2 * padding;

		if(!children.empty()){
			uint maxRowWidth = 0;
			uint rowWidth = 0;

			uint i = 0;
			for(const Element* el : children){
				rowWidth += el->getWidth() + gutter;

				if(++i % cols == 0){
					maxRowWidth = max(maxRowWidth, rowWidth - gutter);
					rowWidth = 0;
				}
			}

			if(rowWidth != 0){
				maxRowWidth = max(maxRowWidth, rowWidth - gutter);
			}

			width += maxRowWidth;
		}
	}

	if(hType == PARENT){
		height = getParent()->getAvailableHeight();
	}else if(hType == CHILDREN && !children.empty()){
		height += 2 * padding;
		uint rowHeight = 0;

		uint i = 0;
		for(const Element* el : children){
			rowHeight = max(rowHeight, el->getHeight());

			if(++i % cols == 0){
				height += rowHeight + gutter;
				rowHeight = 0;
			}
		}

		if(rowHeight == 0){
			rowHeight -= gutter;
		}

		height += rowHeight;
	}


	Serial.println("Reflowing grid layout [" + String(width) + ", " + String(height) + "]");
	Serial.println("W/H Type " + String(wType) + ", " + String(hType) + " [ FIXED, CHILDREN, PARENT ]");

	// call setWidth and setHeight for any potential future functionality
	setWidth(width);
	setHeight(height);

	resize(width, height);
}
