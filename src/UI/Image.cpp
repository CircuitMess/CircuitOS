#include "Image.h"
#include "../Util/Debug.h"

Image::Image(ElementContainer* parent, uint width, uint height) :
	Element(parent), SpriteElement(parent->getSprite(), width, height), width(width), height(height){

}

void Image::draw(){
	sprite.setParent(getParent()->getSprite());
	sprite.setPos(getTotalX(), getTotalY());
	sprite.push();
	Element::draw();
}

uint Image::getWidth(){
	return width;
}

uint Image::getHeight(){
	return height;
}

Sprite* Image::getSprite(){
	return SpriteElement::getSprite();
}
