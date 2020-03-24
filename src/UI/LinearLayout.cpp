#include "LinearLayout.h"
#include "../Util/Debug.h"

LinearLayout::LinearLayout(ElementContainer* parent, LayoutDirection direction) : Layout(parent), direction(direction){

}

void LinearLayout::draw(){
	logln("Drawing linear layout");

	int x = padding;
	int y = padding;

	for(Element* el : children){
		el->setPos(x, y);
		el->draw();

		if(direction == VERTICAL){
			y += gutter + el->getHeight();
		}else if(direction == HORIZONTAL){
			x += gutter + el->getWidth();
		}
	}

	Element::draw();

	// TODO: overflow: draw over padding or erase?
}

void LinearLayout::reflow(){
	if(direction == HORIZONTAL){
		reflowHorizontal();
	}else if(direction == VERTICAL){
		reflowVertical();
	}

	logln("Reflowing linear layout [" + String(getWidth()) + ", " + String(getHeight()) + "]");
	logln("W/H Type " + String(wType) + ", " + String(hType) + " [ FIXED, CHILDREN, PARENT ]");
}

void LinearLayout::reflowHorizontal(){
	if(wType == PARENT){
		setWidth(getParent()->getAvailableWidth());
	}else if(wType == CHILDREN){
		uint width = 2 * padding;

		if(!children.empty()){
			for(Element* el : children){
				width += el->getWidth() + gutter;
			}

			width -= gutter;
		}

		setWidth(width);
	}

	if(hType == PARENT){
		setHeight(getParent()->getAvailableHeight());
	}else if(hType == CHILDREN && !children.empty()){
		uint maxHeight = 0;

		for(Element* el : children){
			maxHeight = max(maxHeight, el->getHeight());
		}

		setHeight(maxHeight + 2 * padding);
	}
}

void LinearLayout::reflowVertical(){
	if(wType == PARENT){
		setWidth(getParent()->getAvailableWidth());
	}else if(wType == CHILDREN && !children.empty()){
		uint maxWidth = 0;

		for(Element* el : children){
			maxWidth = max(maxWidth, el->getWidth());
		}

		setWidth(maxWidth + 2 * padding);
	}

	if(hType == PARENT){
		setHeight(getParent()->getAvailableHeight());
	}else if(hType == CHILDREN){
		uint height = 2 * padding;

		if(!children.empty()){
			for(Element* el : children){
				height += el->getHeight() + gutter;
			}

			height -= gutter;
		}

		setHeight(height);
	}
}
