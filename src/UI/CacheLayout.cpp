#include "CacheLayout.h"
#include "../Util/Debug.h"

CacheLayout::CacheLayout(ElementContainer* parent) : Layout(parent), SpriteElement(parent->getSprite(), 0, 0){

}

Sprite* CacheLayout::getSprite(){
	return SpriteElement::getSprite();
}

uint CacheLayout::getWidth(){
	return Layout::getWidth();
}

uint CacheLayout::getHeight(){
	return Layout::getHeight();
}

int CacheLayout::getTotalX() const{
	return 0;
}

int CacheLayout::getTotalY() const{
	return 0;
}

void CacheLayout::draw(){
	sprite.setPos(Element::getTotalX(), Element::getTotalY());
	sprite.setParent(getParent()->getSprite());
	sprite.push();
}

void CacheLayout::reflow(){
	Layout::reflow();
	sprite.resize(getWidth(), getHeight());
}

void CacheLayout::refresh(){
	sprite.clear(TFT_BLACK);
	ElementContainer::draw();
}

