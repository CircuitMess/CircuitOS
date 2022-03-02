#include "Matrix.h"
#include "Font.hpp"

#ifndef _swap_int16_t
#define _swap_int16_t(a, b)                                                    \
{                                                                            \
    int16_t t = a;                                                             \
    a = b;                                                                     \
    b = t;                                                                     \
}
#endif

/**************************************************************************/
/*!
	@brief Constructor for breakout version.
	@param width Desired width of led display.
	@param height Desired height of led display.
*/
/**************************************************************************/

Matrix::Matrix(MatrixOutput &output, uint8_t _width, uint8_t _height) : output(output){
	width = _width;
	height = _height;
	matrixBuffer = (uint8_t*)calloc(width * height, sizeof(uint8_t));
	pastMatrixBuffer = (uint8_t*)calloc(width * height, sizeof(uint8_t));
}

/**************************************************************************/
/*!
	@brief Initialize hardware and clear display.
*/
/**************************************************************************/
void Matrix::begin(){
	output.init();
	clear(); // set each led to 0 PWM
	push();
	clear();
}

void Matrix::setOutput(MatrixOutput &output){
	Matrix::output = output;
}

/**************************************************************************/
/*!
	@brief Sets all LEDs on & 0 PWM for current frame.
*/
/**************************************************************************/
void Matrix::clear(){
	memset(matrixBuffer, 0, width * height);
}

/**************************************************************************/
/*!
	@brief Low level accesssor - sets a 8-bit PWM pixel value
	handles rotation and pixel arrangement, unlike setLEDPWM
	@param x The x position, starting with 0 for left-most side
	@param y The y position, starting with 0 for top-most side
	@param color Despite being a 16-bit value, takes 0 (off) to 255 (max on)
*/
/**************************************************************************/
void Matrix::drawPixel(int16_t x, int16_t y, uint16_t color){
	switch(getRotation()){
		case 1:_swap_int16_t(x, y);
			x = width - x - 1;
			break;
		case 2:
			x = width - x - 1;
			y = height - y - 1;
			break;
		case 3:_swap_int16_t(x, y);
			y = height - y - 1;
			break;
	}

	if((x < 0) || (x >= 16))
		return;
	if((y < 0) || (y >= 9))
		return;
	if(color > 255)
		color = 255; // PWM 8bit max
	matrixBuffer[x + y * 16] = color;
}

/**************************************************************************/
/*!
	@brief  Draw a single character on the desired position. Uses a standard ASCII 5x7 font.
	@param   x The x position, starting with 0 for left-most side.
	@param   y The y position, starting with 0 for top-most side
	@param   c The character to be displayed.
	@param   _brightness Brightness of the character. Affected by the global setBrightness setting.
	@param   bigFont Flag to use bigger 5x7 or the smaller 3x5 font: true - big font, false - small font.
*/
/**************************************************************************/
void Matrix::drawChar(int32_t x, int32_t y, unsigned char c, uint8_t _brightness, bool bigFont){
	if(bigFont){
		uint8_t column[6];
		uint8_t mask = 0x1;

		for(int8_t i = 0; i < 5; i++) column[i] = pgm_read_byte(font + (c * 5) + i);
		column[5] = 0;

		int8_t j, k;
		for(j = 0; j < 8; j++){
			for(k = 0; k < 5; k++){
				if(column[k] & mask){
					if((x + k) >= 0 && (y + j) >= 0 && (x + k) < width && (y + j) < height){
						drawPixel(x + k, y + j, _brightness);
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
							drawPixel((x + xo + xx) % 16, y + yo + yy, _brightness);
						}
					}
					bits <<= 1;
				}
			}
		}
	}
}

/**************************************************************************/
/*!
	@brief  Draws a character array on the desired position. Uses a standard ASCII 5x7 font.
	@param   x The x position, starting with 0 for left-most side.
	@param   y The y position, starting with 0 for top-most side
	@param   c The character array to be displayed.
	@param   _brightness Brightness of the character. Affected by the global setBrightness setting.
	@param   bigFont Flag to use bigger 5x7 or the smaller 3x5 font: true - big font, false - small font.
*/
/**************************************************************************/
void Matrix::drawString(int32_t x, int32_t y, const char* c, uint8_t _brightness, bool bigFont){
	size_t length = strlen(c);
	for(size_t i = 0; i < length; i++){
		drawChar(x, y, c[i], _brightness, bigFont);
		x += bigFont ? 6 : 4;
	}
}

void Matrix::drawString(int32_t x, int32_t y, const String &s, uint8_t _brightness, bool bigFont){
	drawString(x, y, s.c_str(), _brightness, bigFont);
}

/**************************************************************************/
/*!
	@brief  Sets global brightness for the matrix.
	@param   _brightness Global brightness for the matrix. Ranges from 0 to 255.
*/
/**************************************************************************/
void Matrix::setBrightness(uint8_t _brightness){
	output.setBrightness(_brightness);
}

/**************************************************************************/
/*!
	@brief  Gets global brightness for the matrix.
	@return   Global brightness of the matrix.
*/
/**************************************************************************/
uint8_t Matrix::getBrightness() const{
	return output.getBrightness();
}

/**************************************************************************/
/*!
	@brief  Sets matrix rotation.
	@param   rot Desired rotation in clockwise direction (0-3).
*/
/**************************************************************************/
void Matrix::setRotation(uint8_t rot){
	if(rot > 3) return;
	rotation = rot;
}

/**************************************************************************/
/*!
	@brief  Gets matrix rotation.
	@return   Matrix rotation (0-3).
*/
/**************************************************************************/
uint8_t Matrix::getRotation() const{
	return rotation;
}

/**************************************************************************/
/*!
	@brief  Push the matrix buffer onto the matrix.
*/
/**************************************************************************/
void Matrix::push(){
	output.push(matrixBuffer);
}

/**************************************************************************/
/*!
	@brief  Starts animation. Frames will be updated inside updateAnimation().
	@param  animation Pointer to desired animation.
	@param  loop Sets animation loop. True - loop until stopAnimation() or another startAnimation(), False - no looping.
*/
/**************************************************************************/
void Matrix::startAnimation(Animation* _animation, bool loop){
	stopAnimation();

	animation = _animation;
	animationLoop = loop;
	animationFrame = animation->getNextFrame();
	drawBitmap(0, 0, animation->getWidth(), animation->getHeight(), animationFrame->data);
	push();
	currentFrameTime = 0;
	animationStartMicros = micros();
}

/**************************************************************************/
/*!
	@brief  Stops running animation.
*/
/**************************************************************************/
void Matrix::stopAnimation(){
	delete animation;
	animation = nullptr;
	animationFrame = nullptr;
	currentFrameTime = 0;
}

/**************************************************************************/
/*!
	@brief  Updates running animation. Expected to be used inside loop().
	@param  _time Current millis() time, used for frame duration calculation.
*/
/**************************************************************************/
void Matrix::loop(uint _time){
	if(animationFrame != nullptr && animation != nullptr){
		currentFrameTime += _time;
		if(currentFrameTime >= animationFrame->duration * 1000){
			clear();
			currentFrameTime = 0;
			animationFrame = animation->getNextFrame();
			if(animationFrame == nullptr){
				if(animationLoop){
					animationStartMicros = micros();
					animation->rewind();
					animationFrame = animation->getNextFrame();
				}else{
					stopAnimation();
					return;
				}
			}
			drawBitmap(0, 0, animation->getWidth(), animation->getHeight(), animationFrame->data);
		}
	}
	bool noChange = true;
	if(prevBrightness == output.getBrightness()){
		for(uint8_t i = 0; i < width * height; i++){
			if(matrixBuffer[i] != pastMatrixBuffer[i]){
				noChange = false;
				break;
			}
		}
	}else{
		noChange = false;
		prevBrightness = output.getBrightness();
	}
	if(!noChange){
		push();
	}
	memcpy(pastMatrixBuffer, matrixBuffer, width * height);
}

/**************************************************************************/
/*!
	@brief  Draws a bitmap on the desired position. Expects an 8-bit monochrome array.
	@param   x The x position, starting with 0 for left-most side.
	@param   y The y position, starting with 0 for top-most side.
	@param   width Bitmap width.
	@param   height Bitmap height.
	@param   data Pointer to the bitmap.
*/
/**************************************************************************/
void Matrix::drawBitmap(int x, int y, uint width, uint height, uint8_t* data){
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			drawPixel(x + j, y + i, data[i * width + j]);
		}
	}
}

/**************************************************************************/
/*!
	@brief  Draws a bitmap on the desired position. Expects a 24-bit color array, uses only the red color value.
	@param   x The x position, starting with 0 for left-most side.
	@param   y The y position, starting with 0 for top-most side.
	@param   width Bitmap width.
	@param   height Bitmap height.
	@param   data Pointer to the bitmap.
*/
/**************************************************************************/
void Matrix::drawBitmap(int x, int y, uint width, uint height, RGBpixel* data){
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			drawPixel(x + j, y + i, data[i * width + j].r);
		}
	}
}

/**************************************************************************/
/*!
	@brief  Returns the completion rate in percentage for the current animation.
	@return  Completion rate (in percentage 0-100) for the current animation. If none are played, then defaults to zero.
*/
/**************************************************************************/
float Matrix::getAnimationCompletionRate(){
	if(animationFrame == nullptr || animation == nullptr) return 0.0;
	return ((float)(micros() - animationStartMicros)) / ((float)(animation->getLoopDuration() * 1000)) * 100;
}

void Matrix::drawPixel(uint8_t i, uint8_t brightness){
	matrixBuffer[i] = brightness;
}
