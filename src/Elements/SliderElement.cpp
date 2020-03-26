#include "SliderElement.h"
#include "../Update/UpdateManager.h"

SliderElement::SliderElement(ElementContainer* parent, uint width, uint height) :
		Layout(parent){

	image = new Image(this, width, height);
	addChild(image);
}

SliderElement::~SliderElement(){
	delete image;
}

void SliderElement::reposChildren(){
	uint newPos = getAvailableWidth() - image->getWidth() - getPadding() - progress / speed;
	children[0]->setPos(newPos, 0);
}

void SliderElement::update(uint millis){
	if(started){
		progress += millis;
		reposChildren();
	}

	if(progress / speed > getParent()->getAvailableWidth() - image->getWidth() - 10){
		started = false;

		if(completeListener){
			progress = 0;
			reposChildren();

			completeListener();
		}
	}
}

Sprite* SliderElement::getImageSprite(){
	return image->getSprite();
}

void SliderElement::start(){
	started = true;

	if(startListener) startListener();
}

void SliderElement::stop(){
	started = false;
	uint distance = progress / speed;
	progress = 0;
	reposChildren();

	// TODO: just under full
	if(distance <= 40){
		if(shortListener) shortListener();
	}else if(distance < getParent()->getAvailableWidth() - image->getWidth() - 10){
		if(longListener) longListener();
	}
}

void SliderElement::setStartListener(void (* listener)()){
	SliderElement::startListener = listener;
}

void SliderElement::setStopListener(void (* listener)()){
	SliderElement::startListener = listener;
}

void SliderElement::setShortListener(void (* listener)()){
	SliderElement::shortListener = listener;
}

void SliderElement::setLongListener(void (* listener)()){
	SliderElement::longListener = listener;
}

void SliderElement::setCompleteListener(void (* listener)()){
	SliderElement::completeListener = listener;
}
