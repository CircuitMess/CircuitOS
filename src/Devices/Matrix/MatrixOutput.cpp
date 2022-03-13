#include "MatrixOutput.h"

MatrixOutput::MatrixOutput(uint16_t width, uint16_t height) : width(width), height(height){

}

uint16_t MatrixOutput::getWidth() const{
	return width;
}

uint16_t MatrixOutput::getHeight() const{
	return height;
}

uint8_t MatrixOutput::getBrightness() const{
	return brightness;
}

void MatrixOutput::setBrightness(uint8_t brightness){
	MatrixOutput::brightness = brightness;
}
