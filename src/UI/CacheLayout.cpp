#include "CacheLayout.h"

CacheLayout::CacheLayout(ElementContainer* parent) : Layout(parent), sprite(parent->getSprite(), 0, 0){

}

Sprite* CacheLayout::getSprite(){
	return &sprite;
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
