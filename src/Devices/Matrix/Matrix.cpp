#include "Matrix.h"
#include "Font.hpp"

Matrix::Matrix(MatrixOutput& output) : output(output), width(output.getWidth()), height(output.getHeight()), data(output.getWidth(), output.getHeight()){

}

void Matrix::begin(){
	clear();
	push();
}

void Matrix::clear(){
	data.clear();
}

void Matrix::push(){
	output.push(data);
}

void Matrix::drawPixel(uint16_t x, uint16_t y, const MatrixPixel& color){
	switch(rotation){
		case 1:
			std::swap(x, y);
			x = width - x - 1;
			break;
		case 2:
			x = width - x - 1;
			y = height - y - 1;
			break;
		case 3:
			std::swap(x, y);
			y = height - y - 1;
			break;
	}

	if((x < 0) || (x >= width))
		return;
	if((y < 0) || (y >= height))
		return;

	data[x][y] = color;
}

void Matrix::drawPixel(uint16_t i, const MatrixPixel& color){
	uint16_t y = i / width;
	uint16_t x = i - y * width;
	drawPixel(x, y, color);
}

void Matrix::drawChar(int32_t x, int32_t y, unsigned char c, const MatrixPixel& color){
	if(font == BIG){
		uint8_t column[6];
		uint8_t mask = 0x1;

		for(int8_t i = 0; i < 5; i++) column[i] = pgm_read_byte(font + (c * 5) + i);
		column[5] = 0;

		int8_t j, k;
		for(j = 0; j < 8; j++){
			for(k = 0; k < 5; k++){
				if(column[k] & mask){
					if((x + k) >= 0 && (y + j) >= 0 && (x + k) < width && (y + j) < height){
						drawPixel(x + k, y + j, color);
					}
				}
			}
			mask <<= 1;
		}
	}else{
		if((c >= TomThumb.first) && (c <= TomThumb.last)){
			c -= TomThumb.first;
			GFXglyph* glyph = &(TomThumb.glyph[c]);
			uint8_t* bitmap = TomThumb.bitmap;

			uint16_t bo = pgm_read_word(&glyph->bitmapOffset);
			uint8_t w = pgm_read_byte(&glyph->width),
					h = pgm_read_byte(&glyph->height);
			int8_t xo = pgm_read_byte(&glyph->xOffset),
					yo = pgm_read_byte(&glyph->yOffset);
			uint8_t xx, yy, bits, bit = 0;

			for(yy = 0; yy < h; yy++){
				for(xx = 0; xx < w; xx++){
					if(!(bit++ & 7)){
						bits = pgm_read_byte(&bitmap[bo++]);
					}
					if(bits & 0x80){
						if((x + xo + xx) >= 0 && (y + yo + yy) >= 0 && (x + xo + xx) < width && (y + yo + yy) < height){
							drawPixel((x + xo + xx) % 16, y + yo + yy, color);
						}
					}
					bits <<= 1;
				}
			}
		}
	}
}

void Matrix::drawString(int32_t x, int32_t y, const String &s, const MatrixPixel& color){
	for(size_t i = 0; i < s.length(); i++){
		drawChar(x, y, s[i], color);
		x += font == BIG ? 6 : 4;
	}
}

void Matrix::drawBitmap(uint16_t xPos, uint16_t yPos, uint16_t w, uint16_t h, const uint8_t* data, const MatrixPixel& color){
	MatrixPixel c = color;

	for(int x = 0; x < w; x++){
		for(int y = 0; y < h; y++){
			c.i = data[y * w + x];
			drawPixel(xPos + x, yPos + y, c);
		}
	}
}

void Matrix::drawBitmap(uint16_t xPos, uint16_t yPos, const MatrixPixelData& data){
	for(int x = 0; x < data.getWidth(); x++){
		for(int y = 0; y < data.getHeight(); y++){
			drawPixel(xPos + x, yPos + y, data.get(x, y));
		}
	}
}

void Matrix::startAnimation(MatrixAnim* animation){
	stopAnimation();
	this->animation = animation;
	animation->start();
}

MatrixAnim* Matrix::getAnimation(){
	return animation;
}

void Matrix::stopAnimation(){
	delete animation;
	animation = nullptr;
}

void Matrix::setBrightness(uint8_t _brightness){
	output.setBrightness(_brightness);
}

uint8_t Matrix::getBrightness() const{
	return output.getBrightness();
}

/*void Matrix::setRotation(uint8_t rot){
	if(rot > 3) return;
	rotation = rot;
}

uint8_t Matrix::getRotation() const{
	return rotation;
}*/

Matrix::Font Matrix::getFont() const{
	return font;
}

void Matrix::setFont(Matrix::Font font){
	Matrix::font = font;
}
