#include "Image.h"
#include "../Util/Debug.h"

Image::Image(ElementContainer* parent, uint width, uint height) : width(width), height(height),
	Element(parent), SpriteElement(parent->getSprite(), width, height){

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

void Image::setWidth(uint width){
	Image::width = width;
}

void Image::setHeight(uint height){
	Image::height = height;
}

void Image::setSize(uint width, uint height){
	setWidth(width);
	setHeight(height);
}
