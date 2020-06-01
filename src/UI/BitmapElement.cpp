#include "BitmapElement.h"

BitmapElement::BitmapElement(ElementContainer* parent, const uint16_t* bitmap, uint width, uint height) :
		Element(parent), bitmap(bitmap), width(width), height(height){ }

uint BitmapElement::getWidth(){
	return width;
}

uint BitmapElement::getHeight(){
	return height;
}

void BitmapElement::draw(){
	getSprite()->drawIcon(bitmap, getTotalX(), getTotalY(), width, height, 1, TFT_TRANSPARENT);
}
