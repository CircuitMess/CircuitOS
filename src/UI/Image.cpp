#include "Image.h"
#include "../Util/Debug.h"

Image::Image(ElementContainer* parent, uint width, uint height) :
	Element(parent), width(width), height(height),
	sprite(parent->getSprite(), width, height) {

}

void Image::draw(){
	logln("Drawing image");
	sprite.setParent(Element::getSprite());
	sprite.setPos(getTotalX(), getTotalY());
	sprite.push();
	Element::draw();
}

Sprite* Image::getSprite(){
	return &sprite;
}

uint Image::getWidth(){
	return width;
}

uint Image::getHeight(){
	return height;
}
