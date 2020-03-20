#include "Image.h"
#include "../Util/Debug.h"

Image::Image(ElementContainer* parent, uint width, uint height) : Element(parent), width(width), height(height){
	sprite->resize(width, height);
}

void Image::draw(){
	logln("Drawing image");
	sprite->push();
}

uint Image::getWidth() const{
	return width;
}

uint Image::getHeight() const{
	return height;
}
