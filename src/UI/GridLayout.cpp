#include "GridLayout.h"
#include "../Util/Debug.h"

GridLayout::GridLayout(ElementContainer* parent, uint cols) : Layout(parent), cols(cols){

}

void GridLayout::reflow(){
	if(wType == PARENT){
		setWidth(getParent()->getAvailableWidth());
	}else if(wType == CHILDREN){
		uint width = 2 * padding;

		if(!children.empty()){
			uint maxRowWidth = 0;
			uint rowWidth = 0;

			uint i = 0;
			for(Element* el : children){
				rowWidth += el->getWidth() + gutter;

				if(++i % cols == 0){
					maxRowWidth = max(maxRowWidth, rowWidth - gutter);
					rowWidth = 0;
				}
			}

			if(rowWidth != 0){
				maxRowWidth = max(maxRowWidth, rowWidth - gutter);
			}

			setWidth(width + maxRowWidth);
		}
	}

	if(hType == PARENT){
		setHeight(getParent()->getAvailableHeight());
	}else if(hType == CHILDREN && !children.empty()){
		uint height = 2 * padding;
		uint rowHeight = 0;

		uint i = 0;
		for(Element* el : children){
			rowHeight = max(rowHeight, el->getHeight());

			if(++i % cols == 0){
				height += rowHeight + gutter;
				rowHeight = 0;
			}
		}

		if(rowHeight == 0){
			rowHeight -= gutter;
		}

		setHeight(height + rowHeight);
	}


	logln("Reflowing grid layout [" + String(getWidth()) + ", " + String(getHeight()) + "]");
	logln("W/H Type " + String(wType) + ", " + String(hType) + " [ FIXED, CHILDREN, PARENT ]");
}

void GridLayout::reposChildren(){
	logln("Repositioning grid layout");

	uint x = padding;
	uint y = padding;

	uint col = 0;
	uint maxHeight = 0;
	for(Element* el : children){
		el->setPos(x, y);

		x += el->getWidth() + gutter;
		maxHeight = max(maxHeight, el->getHeight());

		if(++col == cols){
			y += maxHeight + gutter;
			x = padding;
			maxHeight = 0;
			col = 0;
		}
	}
}

void GridLayout::draw(){
	if(!strictPos){
		Layout::draw();
		return;
	}

	uint x = padding;
	uint y = padding;

	uint col = 0;
	uint maxHeight = 0;
	for(Element* el : children){
		el->setPos(x, y);
		logln("GL Setting pos [" + String(x) + ", " + String(y) + "]");
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
}
