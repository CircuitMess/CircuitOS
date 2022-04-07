#include "MatrixAnim.h"
#include "Matrix.h"

MatrixAnim::MatrixAnim(Matrix* matrix) : matrix(matrix), width(matrix->getWidth()), height(matrix->getHeight()){

}

MatrixAnim::~MatrixAnim(){
	stop();
}

void MatrixAnim::start(){
	if(started) return;
	started = true;

	onStart();
}

void MatrixAnim::stop(){
	if(!started) return;
	started = false;

	onStop();
}

bool MatrixAnim::isStarted(){
	return started;
}

void MatrixAnim::setX(int32_t x){
	MatrixAnim::_x = x;
}

void MatrixAnim::setY(int32_t y){
	MatrixAnim::_y = y;
}

void MatrixAnim::drawPixel(uint16_t x, uint16_t y, const MatrixPixel& color){
	matrix->drawPixel(x + _x, y + _y, color);
}

void MatrixAnim::drawPixel(uint16_t i, const MatrixPixel& color){
	drawPixel(i % width, i / width, color);
}

void MatrixAnim::drawChar(int32_t x, int32_t y, unsigned char c, const MatrixPixel& color){
	matrix->drawChar(x + _x, y + _y, c, color);
}

void MatrixAnim::drawString(int32_t x, int32_t y, const String& text, const MatrixPixel& color){
	matrix->drawString(x + _x, y + _y, text, color);
}

void MatrixAnim::drawBitmap(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t* data, const MatrixPixel& color){
	matrix->drawBitmap(x + _x, y + _y, width, height, data, color);
}

void MatrixAnim::drawBitmap(uint16_t x, uint16_t y, const MatrixPixelData& data){
	matrix->drawBitmap(x + _x, y + _y, data);
}

void MatrixAnim::push(){
	matrix->push();
}

void MatrixAnim::clear(){
	for(uint32_t x = 0; x < width; x++){
		for(uint32_t y = 0; y < height; y++){
			drawPixel(x, y, {0, 0, 0, 0});
		}
	}
}

void MatrixAnim::setWidth(uint32_t width){
	MatrixAnim::width = width;
}

void MatrixAnim::setHeight(uint32_t height){
	MatrixAnim::height = height;
}

int32_t MatrixAnim::getX() const{
	return _x;
}

int32_t MatrixAnim::getY() const{
	return _y;
}

uint32_t MatrixAnim::getWidth() const{
	return width;
}

uint32_t MatrixAnim::getHeight() const{
	return height;
}
