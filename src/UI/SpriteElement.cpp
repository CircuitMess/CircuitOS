#include "SpriteElement.h"

SpriteElement::SpriteElement(Sprite* parentSprite, uint width, uint height) : sprite(parentSprite, width, height){

}

SpriteElement::~SpriteElement(){ }

Sprite* SpriteElement::getSprite(){
	return &sprite;
}

void SpriteElement::pack(){
	sprite.cleanup();
}

void SpriteElement::unpack(){
	sprite.resize(getWidth(), getHeight());
}
