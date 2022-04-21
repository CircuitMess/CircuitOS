#include "MatrixAnim.h"
#include "Matrix.h"

MatrixAnim::MatrixAnim(Matrix* matrix) : matrix(matrix){
	if(matrix){
		width = matrix->getWidth();
		height = matrix->getHeight();
	}
}

MatrixAnim::~MatrixAnim(){

}

void MatrixAnim::start(){
	if(matrix == nullptr) return;

	if(started) return;
	started = true;

	matrix->addAnim(this);

	onStart();
}

void MatrixAnim::stop(){
	if(!started) return;
	started = false;

	if(matrix){
		matrix->removeAnim(this);
	}

	onStop();
}

bool MatrixAnim::isStarted(){
	return started;
}

void MatrixAnim::setX(int32_t x){
	posX = x;
}

void MatrixAnim::setY(int32_t y){
	posY = y;
}

void MatrixAnim::drawPixel(uint16_t x, uint16_t y, const MatrixPixel& color){
	matrix->drawPixel(x + posX, y + posY, color);
}

void MatrixAnim::drawPixel(uint16_t i, const MatrixPixel& color){
	drawPixel(i % width, i / width, color);
}

void MatrixAnim::drawChar(int32_t x, int32_t y, unsigned char c, const MatrixPixel& color){
	matrix->drawChar(x + posX, y + posY, c, color);
}

void MatrixAnim::drawString(int32_t x, int32_t y, const String& text, const MatrixPixel& color){
	matrix->drawString(x + posX, y + posY, text, color);
}

void MatrixAnim::drawBitmap(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t* data, const MatrixPixel& color){
	matrix->drawBitmap(x + posX, y + posY, width, height, data, color);
}

void MatrixAnim::drawBitmap(uint16_t x, uint16_t y, const MatrixPixelData& data){
	matrix->drawBitmap(x + posX, y + posY, data);
}

void MatrixAnim::pushMatrix(){
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
	return posX;
}

int32_t MatrixAnim::getY() const{
	return posY;
}

uint32_t MatrixAnim::getWidth() const{
	return width;
}

uint32_t MatrixAnim::getHeight() const{
	return height;
}

void MatrixAnim::setMatrix(Matrix* matrix){
	if(this->matrix == nullptr && width == 0 && height == 0){
		width = matrix->getWidth();
		height = matrix->getHeight();
	}

	this->matrix = matrix;
}
