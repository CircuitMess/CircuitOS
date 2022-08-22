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
				loopDoneCallback(loopCount);
				return;
			}
		}
	}
}

void GIFAnimatedSprite::start(){
	if(!gif) return;
	LoopManager::addListener(this);
	gif.nextFrame();
}

void GIFAnimatedSprite::stop(){
	LoopManager::removeListener(this);

}

void GIFAnimatedSprite::push() const{
	if(!gif) return;

	parentSprite->drawIcon(gif.getFrame().getData(), getX(), getY(), getWidth(), getHeight(), scale);
}

void GIFAnimatedSprite::push(Sprite* sprite, int x, int y, Color maskingColor) const{
	if(!gif) return;

	sprite->drawIcon(gif.getFrame().getData(), x, y, getWidth(), getHeight(), scale, maskingColor);
}

#ifdef CIRCUITOS_LOVYANGFX
void GIFAnimatedSprite::pushRotate(Sprite* sprite, int x, int y, float rot, Color maskingColor) const{
	if(!gif) return;

	Sprite temp = Sprite(sprite, getWidth(), getHeight());
	temp.clear(TFT_TRANSPARENT);
	temp.drawIcon(gif.getFrame().getData(), 0, 0, getWidth(), getHeight(), 1, maskingColor);
	temp.pushRotateZoomWithAA(x + getWidth() / 2, y + getHeight() / 2, rot, scale, scale, TFT_TRANSPARENT);
//	sprite->pushImageRotateZoomWithAA(x, y, getWidth() / 2, getHeight() / 2, rot, scale, scale, getWidth(), getHeight(), (uint8_t*)gif.getFrame().getData(), maskingColor);
}
#endif

void GIFAnimatedSprite::reset(){
	if(!gif) return;

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
	if(!gif) return 0;
	return gif.getWidth();
}

uint16_t GIFAnimatedSprite::getHeight() const{
	if(!gif) return 0;
	return gif.getHeight();
}

GIF::LoopMode GIFAnimatedSprite::getLoopMode() const{
	if(!gif) GIF::LoopMode::Auto;
	return gif.getLoopMode();
}

void GIFAnimatedSprite::setLoopMode(GIF::LoopMode loopMode){
	if(!gif) return;
	gif.setLoopMode(loopMode);
}

uint32_t GIFAnimatedSprite::getLoopCount() const{
	if(!gif) 0;
	return gif.getLoopCount();
}

void GIFAnimatedSprite::setLoopDoneCallback(std::function<void(uint32_t loopCount)> callback){
	loopDoneCallback = callback;
}

void GIFAnimatedSprite::setScale(uint8_t scale){
	GIFAnimatedSprite::scale = scale;
}
