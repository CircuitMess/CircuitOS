#include "TextElement.h"

TextElement::TextElement(ElementContainer* parent, uint width, uint height) :
	Element(parent), width(width), height(height){

}

TextElement& TextElement::setFont(uint font){
	TextElement::textFont = font;
	return *this;
}

TextElement& TextElement::setSize(uint size){
	TextElement::textSize = size;
	return *this;
}

TextElement& TextElement::setColor(Color color){
	TextElement::textColor = color;
	return *this;
}

void TextElement::draw(){
	Sprite* canvas = getSprite();
	canvas->setTextFont(textFont);
	canvas->setTextColor(textColor);
	canvas->setTextSize(textSize);
	canvas->setCursor(getTotalX(), getTotalY());
	canvas->print(text.c_str());
}

const std::string& TextElement::getText() const{
	return text;
}

void TextElement::setText(const std::string& text){
	TextElement::text = text;
}

uint TextElement::getWidth(){
	return width;
}

uint TextElement::getHeight(){
	return height;
}

void TextElement::setWidth(uint width){
	TextElement::width = width;
}

void TextElement::setHeight(uint height){
	TextElement::height = height;
}
