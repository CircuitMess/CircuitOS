#include <Loop/LoopManager.h>
#include "GIFAnimatedSprite.h"

GIFAnimatedSprite::GIFAnimatedSprite(Sprite* parentSprite, const fs::File& gifFile) : parentSprite(parentSprite), gif(gifFile){
	if(!gif){
		Serial.println("Failed opening gif");
		return;
	}
}

GIFAnimatedSprite::~GIFAnimatedSprite(){
	stop();
}

void GIFAnimatedSprite::loop(uint micros){
	if(!gif) return;

	frameCounter += micros;

	while(frameCounter / 1000 >= gif.frameDuration()){
		frameCounter -= gif.frameDuration()*1000;
		gif.nextFrame();

		if(gif.getLoopCount() > loopCount){
			loopCount = gif.getLoopCount();

			if(loopDoneCallback){
				loopDoneCallback();
			}
		}
	}
}

void GIFAnimatedSprite::start(){
	LoopManager::addListener(this);
}

void GIFAnimatedSprite::stop(){
	LoopManager::removeListener(this);

}

void GIFAnimatedSprite::push() const{
	if(!gif) return;

	parentSprite->drawIcon(gif.getFrame().getData(), getX(), getY(), getWidth(), getHeight(), scale);
}

void GIFAnimatedSprite::push(Sprite* sprite, int x, int y) const{
	if(!gif) return;

	sprite->drawIcon(gif.getFrame().getData(), x, y, getWidth(), getHeight(), scale);
}

void GIFAnimatedSprite::reset(){
	gif.reset();

	frameCounter = 0;
	loopCount = 0;
}

int GIFAnimatedSprite::getX() const{
	return x;
}

void GIFAnimatedSprite::setX(int x){
	GIFAnimatedSprite::x = x;
}

int GIFAnimatedSprite::getY() const{
	return y;
}

void GIFAnimatedSprite::setY(int y){
	GIFAnimatedSprite::y = y;
}

void GIFAnimatedSprite::setXY(int x, int y){
	GIFAnimatedSprite::x = x;
	GIFAnimatedSprite::y = y;
}

uint16_t GIFAnimatedSprite::getWidth() const{
	return gif.getWidth();
}

uint16_t GIFAnimatedSprite::getHeight() const{
	return gif.getHeight();
}

GIF::LoopMode GIFAnimatedSprite::getLoopMode() const{
	return gif.getLoopMode();
}

void GIFAnimatedSprite::setLoopMode(GIF::LoopMode loopMode){
	gif.setLoopMode(loopMode);
}

uint32_t GIFAnimatedSprite::getLoopCount() const{
	return gif.getLoopCount();
}

void GIFAnimatedSprite::setLoopDoneCallback(std::function<void()> callback){
	loopDoneCallback = callback;
}

void GIFAnimatedSprite::setScale(uint8_t scale){
	GIFAnimatedSprite::scale = scale;
}
