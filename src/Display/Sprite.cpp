#include "Display.h" // Sprite.h is included by Display.h
#include "Sprite.h"


Sprite::Sprite(TFT_eSPI* spi, uint8_t width, uint8_t height) : TFT_eSprite(spi){
	parent = nullptr;
	parentSPI = spi;
	createSprite(width, height);
}

Sprite::Sprite(Display& display, uint8_t width, uint8_t height) : TFT_eSprite(display.getBaseSprite()) {
	parent = display.getBaseSprite();
	createSprite(width, height);
}

Sprite::Sprite(Sprite* sprite, uint8_t width, uint8_t height) : TFT_eSprite(sprite){
	parent = sprite;
	createSprite(width, height);
}

void Sprite::cleanup(){
	deleteSprite();
}

Sprite& Sprite::push(){
	if(!_created || _bpp != 16) return *this;

	if(parent == nullptr){
		TFT_eSprite::pushSprite(x, y);
		return *this;
	}

	Serial.println("Pushing sprite at [" + String(x) + ", " + String(y) + "]");

	bool oldSwapBytes = parent->getSwapBytes();
	parent->setSwapBytes(true);
	if(chroma){
		parent->pushImage(x, y, _iwidth, _iheight, _img, chromaKey);
	}else{
		static_cast<TFT_eSprite*>(parent)->pushImage(x, y, _iwidth, _iheight, _img);
	}
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

Sprite& Sprite::resize(uint width, uint height){
	deleteSprite();
	createSprite(width, height);
}

Sprite& Sprite::setTransparent(bool transparent){
	chroma = transparent;
}

Sprite& Sprite::setChroma(uint32_t color){
	chromaKey = color;
	chroma = true;
}

void Sprite::pushData(uint width, uint height, uint16_t* data){
	memcpy(_img, data, sizeof(uint16_t) * width * height);
}

void Sprite::pushImage(int32_t x, int32_t y, int32_t w, int32_t h, uint16_t *data, uint32_t chroma){
	if((x >= _iwidth) || (y >= _iheight) || (w == 0) || (h == 0) || !_created || _bpp != 16) return;
	if((x + w < 0) || (y + h < 0)) return;

	int32_t xo = 0;
	int32_t yo = 0;

	int32_t xs = x;
	int32_t ys = y;

	int32_t ws = w;
	int32_t hs = h;

	if(x < 0){ xo = -x; ws += x; xs = 0; }
	if(y < 0){ yo = -y; hs += y; ys = 0; }

	if(xs + ws >= (int32_t) _iwidth) ws = _iwidth - xs;
	if(ys + hs >= (int32_t) _iheight) hs = _iheight - ys;

	chroma = (uint16_t) (chroma >> 8 | chroma << 8);

	for(int32_t yp = yo; yp < yo + hs; yp++){
		x = xs;
		for(int32_t xp = xo; xp < xo + ws; xp++){
			uint16_t color = data[xp + yp * w];
			if(color == chroma){
				x++;
				continue;
			}

			if(!_iswapBytes) color = color << 8 | color >> 8;
			_img[x + ys * _iwidth] = color;
			x++;
		}
		ys++;
	}
}
