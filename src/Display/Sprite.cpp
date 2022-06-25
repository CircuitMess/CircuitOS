#include "Display.h" // Sprite.h is included by Display.h
#include "Sprite.h"
#include "../Util/Debug.h"
#include <pgmspace.h>

#ifndef CIRCUITOS_LOVYANGFX
#ifdef CIRCUITOS_U8G2FONTS
FontWriter u8f;
#endif
#endif

Sprite::Sprite(TFT_eSPI* spi, uint16_t width, uint16_t height) : TFT_eSprite(spi){
	parent = nullptr;
	parentSPI = spi;
	setColorDepth(16);
#ifdef CIRCUITOS_LOVYANGFX
	setPsram(true);
#endif
	createSprite(width, height);
}

Sprite::Sprite(Display& display, uint16_t width, uint16_t height) : TFT_eSprite(display.getBaseSprite()){
	parent = display.getBaseSprite();
	setColorDepth(16);
#ifdef CIRCUITOS_LOVYANGFX
	setPsram(true);
#endif
	createSprite(width, height);
}

Sprite::Sprite(Sprite* sprite, uint16_t width, uint16_t height) : TFT_eSprite(sprite){
	parent = sprite;
	setColorDepth(16);
#ifdef CIRCUITOS_LOVYANGFX
	setPsram(true);
#endif
	createSprite(width, height);
}

void Sprite::cleanup(){
	deleteSprite();
}

bool Sprite::created(){
	return (_img != nullptr);
}

void Sprite::drawIcon(const unsigned short* icon, int16_t x, int16_t y, uint16_t width, uint16_t height, uint8_t scale, int32_t maskingColor){
	Color c = chromaKey;
	setChroma(TFT_TRANSPARENT);

	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			uint16_t color = pgm_read_word(&icon[j * width + i]);

			if((!chroma || color != chromaKey) && (color != maskingColor || maskingColor == -1)){
				fillRect(x + i * scale, y + j * scale, scale, scale, color);
			}
		}
	}
	setChroma(c);
}

void Sprite::drawIcon(const Pixel* icon, int16_t x, int16_t y, uint16_t width, uint16_t height, uint8_t scale, int32_t maskingColor){
	Color c = chromaKey;
	setChroma(TFT_TRANSPARENT);

	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			Pixel p = icon[j * width + i];
			uint16_t color = C_RGB(p.r, p.g, p.b);

			if((!chroma || color != chromaKey) && (color != maskingColor || maskingColor == -1)){
				fillRect(x + i * scale, y + j * scale, scale, scale, color);
			}
		}
	}
	setChroma(c);
}

void Sprite::drawIcon(File icon, int16_t x, int16_t y, uint16_t width, uint16_t height, uint8_t scale, int32_t maskingColor){
	Color c = chromaKey;
	setChroma(TFT_TRANSPARENT);

	icon.seek(0);
	Color* buffer = (Color*) malloc(1024);
	size_t bufferPos = 0;
	size_t available = icon.read(reinterpret_cast<uint8_t*>(buffer), 1024) / 2;

	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			if(bufferPos == available){
				available = icon.read(reinterpret_cast<uint8_t*>(buffer), 1024) / 2;
				if(available == 0){
					setChroma(c);
					free(buffer);
					return;
				}
				bufferPos = 0;
			}

			uint16_t color = buffer[bufferPos++];

			if((!chroma || color != chromaKey) && (color != maskingColor || maskingColor == -1)){
				fillRect(x + j * scale, y + i * scale, scale, scale, color);
			}
		}
	}
	setChroma(c);
	free(buffer);
}

void Sprite::drawMonochromeIcon(const byte* icon, int16_t x, int16_t y, uint16_t width, uint16_t height, uint8_t scale, uint16_t _color){
	Color c = chromaKey;
	setChroma(_color);

	uint16_t byteWidth = (width + 7) / 8;
	uint16_t _x = x;
	uint16_t dw = 8 - (width % 8);
	for(uint16_t j = 0; j < height; j++){
		x = _x;
		for(uint16_t i = 0; i < byteWidth;){

			uint16_t b = pgm_read_byte(icon++);
			i++;
			for(uint16_t k = 0; k < 8; k++){
				if(i == byteWidth && k == dw){
					x += (width % 8);
					break;
				}
				if(b & 0x80){
					fillRect(x, y, scale, scale, _color);
				}
				b <<= 1;
				x += scale;
			}
		}
		y += scale;
	}
	setChroma(c);
}
void Sprite::drawMonochromeIcon(bool* icon, int16_t x, int16_t y, uint16_t width, uint16_t height, uint8_t scale, uint16_t _color){
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
	int8_t cursorBuffer = getCursorY();
	setCursor(-50, -50);
	uint16_t textLength = getCursorX();
	print(text);
	textLength = getCursorX() - textLength;
	setCursor(int((width() - textLength) / 2), cursorBuffer);
	print(text);
}
void Sprite::printCenter(String text)
{
	int8_t cursorBuffer = getCursorY();
	setCursor(-50, -50);
	uint16_t textLength = getCursorX();
	print(text);
	textLength = getCursorX() - textLength;
	setCursor(int((width() - textLength) / 2), cursorBuffer);
	print(text);
}
void Sprite::printCenter(uint32_t text)
{
	int8_t cursorBuffer = getCursorY();
	setCursor(-50, -50);
	uint16_t textLength = getCursorX();
	print(text);
	textLength = getCursorX() - textLength;
	setCursor(int((width() - textLength) / 2), cursorBuffer);
	print(text);
}
void Sprite::printCenter(int text)
{
	int8_t cursorBuffer = getCursorY();
	setCursor(-50, -50);
	uint16_t textLength = getCursorX();
	print(text);
	textLength = getCursorX() - textLength;
	setCursor(int((width() - textLength) / 2), cursorBuffer);
	print(text);
}
void Sprite::printCenter(float text)
{
	int8_t cursorBuffer = getCursorY();
	setCursor(-50, -50);
	uint16_t textLength = getCursorX();
	print(text);
	textLength = getCursorX() - textLength;
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
				uint16_t temp = ((uint16_t*)(_img))[x * N + y];

				// move values from right to top
				((uint16_t*)(_img))[x * N + y] = ((uint16_t*)(_img))[y * N + N - 1 - x];

				// move values from bottom to right
				((uint16_t*)(_img))[y * N + N - 1 - x] = ((uint16_t*)(_img))[N * (N - 1 - x) + N - 1 - y];

				// move values from left to bottom
				((uint16_t*)(_img))[N * (N - 1 - x) + N - 1 - y] = ((uint16_t*)(_img))[N * (N - 1 - y) + x];

				// assign temp to left
				((uint16_t*)(_img))[N * (N - 1 - y) + x] = temp;
			}
		}
	}
}

Sprite& Sprite::push(){
	if((_img == nullptr) || _bpp != 16) return *this;
#ifdef CIRCUITOS_LOVYANGFX
	TFT_eSprite::pushSprite(x, y, TFT_TRANSPARENT);
	return *this;
#else
	if(parent == nullptr){
		TFT_eSprite::pushSprite(x, y);
		return *this;
	}

	logln("Pushing sprite at [" + String(x) + ", " + String(y) + "]");

	bool oldSwapBytes = parent->getSwapBytes();
	if(getSwapBytes()){
		parent->setSwapBytes(!parent->getSwapBytes());
	}

	if(chroma){
		parent->pushImage(x, y, width(), height(), _img, (uint32_t) chromaKey);
	}else{
		static_cast<TFT_eSprite*>(parent)->pushImage(x, y, width(), height(), _img);
	}
	parent->setSwapBytes(oldSwapBytes);

	return *this;
#endif
}

Sprite& Sprite::clear(uint16_t color){
	TFT_eSprite::fillSprite(color);
	return *this;
}

Sprite& Sprite::setPos(int32_t x, int32_t y){
	this->x = x;
	this->y = y;
	return *this;
}

Sprite& Sprite::resize(uint width, uint height){
	if(!(_img != nullptr)){
		createSprite(width, height);
		return *this;
	}

	deleteSprite();
	logln("Resizing sprite to [" + String(width) + ", " + String(height) + "]");
	if(createSprite(width, height) == nullptr){
		logln("CreateSprite failed");
	}

	if((_img != nullptr) == false){
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
#ifndef CIRCUITOS_LOVYANGFX
void Sprite::pushImage(int32_t x, int32_t y, int32_t w, int32_t h, uint16_t *data, uint32_t chroma){
	if((x >= width()) || (y >= height()) || (w == 0) || (h == 0) || !(_img != nullptr) || _bpp != 16) return;
	if((x + w < 0) || (y + h < 0)) return;

	int32_t xo = 0;
	int32_t yo = 0;

	int32_t xs = x;
	int32_t ys = y;

	int32_t ws = w;
	int32_t hs = h;

	if(x < 0){ xo = -x; ws += x; xs = 0; }
	if(y < 0){ yo = -y; hs += y; ys = 0; }

	if(xs + ws >= (int32_t) width()) ws = width() - xs;
	if(ys + hs >= (int32_t) height()) hs = height() - ys;

	chroma = (uint16_t) (chroma >> 8 | chroma << 8);

	for(int32_t yp = yo; yp < yo + hs; yp++){
		x = xs;
		for(int32_t xp = xo; xp < xo + ws; xp++){
			uint16_t color = data[xp + yp * w];
			if(color == chroma){
				x++;
				continue;
			}

			if(!getSwapBytes()) color = color << 8 | color >> 8;
			((uint16_t*)(_img))[x + ys * width()] = color;
			x++;
		}
		ys++;
	}
}
#endif
int32_t Sprite::getX() const{
	return x;
}

int32_t Sprite::getY() const{
	return y;
}

void Sprite::setParent(Sprite* parent){
	Sprite::parent = parent;
#ifdef CIRCUITOS_LOVYANGFX
	if(parent == nullptr){
		TFT_eSprite::_parent = parentSPI;
	}else{
		TFT_eSprite::_parent = parent;
	}
#endif
}

Sprite* Sprite::getParent() const{
	return parent;
}

Sprite::~Sprite(){
	deleteSprite();
}

#ifndef CIRCUITOS_LOVYANGFX
#ifdef CIRCUITOS_U8G2FONTS
FontWriter& Sprite::startU8g2Fonts(){
	u8f.begin(*this);
	return u8f;
}
#endif
#endif
