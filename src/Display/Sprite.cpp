#include "Sprite.h"

Sprite::Sprite(Display& display, uint8_t width, uint8_t height) : TFT_eSprite(&display.getBaseSprite()) {
		parent = &display.getBaseSprite();
		createSprite(width, height);
}

Sprite::Sprite(Sprite* sprite, uint8_t width, uint8_t height) : TFT_eSprite(sprite){
	parent = sprite;
	createSprite(width, height);
}

Sprite& Sprite::push(){
	if(!_created || _bpp != 16) return *this;

	bool oldSwapBytes = parent->getSwapBytes();
	parent->setSwapBytes(true);
	parent->pushImage(x, y, _iwidth, _iheight, _img);
	parent->setSwapBytes(oldSwapBytes);

	return *this;
}

Sprite& Sprite::clear(uint32_t color){
	TFT_eSprite::fillSprite(color);
	return *this;
}

Sprite& Sprite::setPos(uint16_t x, uint16_t y){
	this->x = x;
	this->y = y;
	return *this;
}
