#include "Image.h"

Image::Image(ElementContainer* parent, uint width, uint height) : Element(parent), width(width), height(height){
	sprite->resize(width, height);
}

void Image::draw(){
	Serial.println("Drawing image");
	sprite->push();
}

uint Image::getWidth() const{
	return width;
}

uint Image::getHeight() const{
	return height;
}
