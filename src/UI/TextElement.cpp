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

void TextElement::setAlignment(TextElement::TextAlignment alignment){
	this->textAlignment = alignment;
}

void TextElement::draw(){
	Sprite* canvas = getSprite();
	canvas->setTextFont(textFont);
	canvas->setTextColor(textColor);
	canvas->setTextSize(textSize);

	canvas->setCursor(-255, -255);
	canvas->print(text.c_str());
	uint textWidth = canvas->getCursorX() + 255;
	canvas->setCursor(-255, -255);
	canvas->println(text.c_str());
	uint textHeight = canvas->getCursorY() + 255;

	uint textX;
	switch(textAlignment){
		default:
		case LEFT:
			textX = 0;
			break;
		case CENTER:
			textX = (width - textWidth) / 2;
			break;
		case RIGHT:
			textX = width - textWidth;
			break;
	}

	canvas->setCursor(getTotalX() + textX, getTotalY() + (height - textHeight) / 2 + 1);
	canvas->print(text.c_str());
	Element::draw();
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
