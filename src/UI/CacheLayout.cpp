#include "CacheLayout.h"

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

void CacheLayout::draw(){
	sprite.setPos(getTotalX(), getTotalY());
	sprite.setParent(getParent()->getSprite());
	sprite.push();
}

void CacheLayout::reflow(){
	Layout::reflow();
	sprite.resize(getWidth(), getHeight());
}

void CacheLayout::refresh(){
	ElementContainer::draw();
}

