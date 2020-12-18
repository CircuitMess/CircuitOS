#include "Display.h" // Sprite.h is included by Display.h
#include "Sprite.h"
#include "../Util/Debug.h"
#include <pgmspace.h>


Sprite::Sprite(TFT_eSPI* spi, uint16_t width, uint16_t height) : TFT_eSprite(spi){
	parent = nullptr;
	parentSPI = spi;
	createSprite(width, height);
}

Sprite::Sprite(Display& display, uint16_t width, uint16_t height) : TFT_eSprite(display.getBaseSprite()) {
	parent = display.getBaseSprite();
	createSprite(width, height);
}

Sprite::Sprite(Sprite* sprite, uint16_t width, uint16_t height) : TFT_eSprite(sprite){
	parent = sprite;
	createSprite(width, height);
}

void Sprite::cleanup(){
	deleteSprite();
}

bool Sprite::created(){
	return _created;
}

void Sprite::drawIcon(const unsigned short* icon, int16_t x, int16_t y, uint16_t width, uint16_t height, uint8_t scale, int32_t maskingColor){
	Color c = chromaKey;
	setChroma(TFT_TRANSPARENT);

	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			uint32_t color = pgm_read_word(&icon[j * width + i]);

			if((!chroma || color != chromaKey) && (color != maskingColor || maskingColor == -1)){
				fillRect(x + i * scale, y + j * scale, scale, scale, color);
			}
		}
	}
	setChroma(c);
}
void Sprite::drawMonochromeIcon(const byte* icon, int16_t x, int16_t y, uint16_t width, uint16_t height, uint8_t scale, uint32_t _color){
	Color c = chromaKey;
	setChroma(_color);

	uint16_t byteWidth = (width + 7) / 8;
	uint16_t _x = x;
	uint16_t dw = 8 - (width % 8);
	for (uint16_t j = 0; j < height; j++) {
		x = _x;
		for (uint16_t i = 0; i < byteWidth;) {
			
			uint16_t b = pgm_read_byte(icon++);
			i++;
			for (uint16_t k = 0; k < 8; k++) {
				if (i == byteWidth && k == dw) {
					x += (width % 8);
					break;
				}
				if (b & 0x80) {
					fillRect(x, y, scale, scale, _color);
				} 
				b <<= 1;
				x+=scale;
			}
		}
		y+=scale;
	}
	setChroma(c);
}
void Sprite::drawMonochromeIcon(bool* icon, int16_t x, int16_t y, uint16_t width, uint16_t height, uint8_t scale, uint32_t _color){
	Color c = chromaKey;
	setChroma(_color);

	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			if(icon[j * width + i]){
				fillRect(x + i * scale, y + j * scale, scale, scale, _color);
			}
		}
	}
	setChroma(c);
}
void Sprite::printCenter(const char* text)
{
	int8_t cursorBuffer = cursor_y;
	setCursor(-50, -50);
	uint16_t textLength = cursor_x;
	print(text);
	textLength = cursor_x - textLength;
	setCursor(int((width() - textLength) / 2), cursorBuffer);
	print(text);
}
void Sprite::printCenter(String text)
{
	int8_t cursorBuffer = cursor_y;
	setCursor(-50, -50);
	uint16_t textLength = cursor_x;
	print(text);
	textLength = cursor_x - textLength;
	setCursor(int((width() - textLength) / 2), cursorBuffer);
	print(text);
}
void Sprite::printCenter(uint32_t text)
{
	int8_t cursorBuffer = cursor_y;
	setCursor(-50, -50);
	uint16_t textLength = cursor_x;
	print(text);
	textLength = cursor_x - textLength;
	setCursor(int((width() - textLength) / 2), cursorBuffer);
	print(text);
}
void Sprite::printCenter(int text)
{
	int8_t cursorBuffer = cursor_y;
	setCursor(-50, -50);
	uint16_t textLength = cursor_x;
	print(text);
	textLength = cursor_x - textLength;
	setCursor(int((width() - textLength) / 2), cursorBuffer);
	print(text);
}
void Sprite::printCenter(float text)
{
	int8_t cursorBuffer = cursor_y;
	setCursor(-50, -50);
	uint16_t textLength = cursor_x;
	print(text);
	textLength = cursor_x - textLength;
	setCursor(int((width() - textLength) / 2), cursorBuffer);
	print(text);
}
void Sprite::rotate(uint times){
	if(width() != height()) return;
	uint N = width();

	for(int i = 0; i < times; i++){
		// Courtesy of GeeksforGeeks https://www.geeksforgeeks.org/inplace-rotate-square-matrix-by-90-degrees/

		// Consider all squares one by one
		for(int x = 0; x < N / 2; x++){
			// Consider elements in group of 4 in
			// current square
			for(int y = x; y < N - x - 1; y++){
				// store current cell in temp variable
				uint16_t temp = _img[x * N + y];

				// move values from right to top
				_img[x * N + y] = _img[y * N + N - 1 - x];

				// move values from bottom to right
				_img[y * N + N - 1 - x] = _img[N * (N - 1 - x) + N - 1 - y];

				// move values from left to bottom
				_img[N * (N - 1 - x) + N - 1 - y] = _img[N * (N - 1 - y) + x];

				// assign temp to left
				_img[N * (N - 1 - y) + x] = temp;
			}
		}
	}
}

Sprite& Sprite::push(){
	if(!_created || _bpp != 16) return *this;

	if(parent == nullptr){
		TFT_eSprite::pushSprite(x, y);
		return *this;
	}

	logln("Pushing sprite at [" + String(x) + ", " + String(y) + "]");

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

Sprite& Sprite::setPos(int32_t x, int32_t y){
	this->x = x;
	this->y = y;
	return *this;
}

Sprite& Sprite::resize(uint width, uint height){
	if(!_created){
		createSprite(width, height);
		return *this;
	}

	deleteSprite();
	logln("Resizing sprite to [" + String(width) + ", " + String(height) + "]");
	if(createSprite(width, height, 1) == nullptr){
		logln("CreateSprite failed");
	}

	if(_created == false){
		logln("Sprite not cretaed");
	}
}

Sprite& Sprite::setTransparent(bool transparent){
	chroma = transparent;
}

Sprite& Sprite::setChroma(Color color){
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

int32_t Sprite::getX() const{
	return x;
}

int32_t Sprite::getY() const{
	return y;
}

void Sprite::setParent(Sprite* parent){
	Sprite::parent = parent;
}

Sprite* Sprite::getParent() const{
	return parent;
}

Sprite::~Sprite(){
	deleteSprite();
}
