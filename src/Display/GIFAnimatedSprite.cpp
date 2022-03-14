#include "GIFAnimatedSprite.h"
#include "../Util/gifdec.h"

GIFAnimatedSprite::GIFAnimatedSprite(Sprite* parentSprite, fs::File _gifFile) : parentSprite(parentSprite), gifFile(_gifFile){
	gif = gd_open_gif(gifFile);
	if(gif == nullptr){
		Serial.println("Failed opening gif");
		return;
	}

	width = gif->width;
	height = gif->height;

	if(!nextFrame()) return;

}

GIFAnimatedSprite::~GIFAnimatedSprite(){
	gd_close_gif(gif);
	free(currentFrame.data);
	gifFile.close();
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

void GIFAnimatedSprite::push(){
	if(currentFrameTime == 0){
		parentSprite->drawIcon(reinterpret_cast<const unsigned short*>(currentFrame.data), x, y, width, height, scale, TFT_TRANSPARENT);
		currentFrameTime = millis();
		return;
	}

	uint cFrameTime = currentFrameTime;
	uint currentTime = millis();
	while(cFrameTime + currentFrame.duration < currentTime){
		cFrameTime += currentFrame.duration;
		currentFrameTime = currentTime;
		if(!nextFrame()){
			if(loopDoneCallback != nullptr && !alerted){
				loopDoneCallback();
				alerted = true;
			}
		}else{
			alerted = false;
		}
	}
	parentSprite->drawIcon(reinterpret_cast<const unsigned short*>(currentFrame.data), x, y, width, height, scale, TFT_TRANSPARENT);
}

void GIFAnimatedSprite::reset(){
	gd_rewind(gif);
	if(!nextFrame()) return;
	currentFrameTime = 0;
	alerted=false;
}

void GIFAnimatedSprite::setLoopDoneCallback(void (*callback)()){
	loopDoneCallback = callback;
}

bool GIFAnimatedSprite::nextFrame(){
	if(gd_get_frame(gif) == 1) {
		if(currentFrame.data != nullptr){
			free(currentFrame.data);
		}
		uint8_t *buffer = (uint8_t*) malloc(width * height * 3);
		//render 24-bit color frame into buffer

		gd_render_frame(gif, buffer, false);

		uint16_t* frame = static_cast<uint16_t*>(malloc(width * height * sizeof(uint16_t)));
		for(int i = 0; i < width * height; i++){
			frame[i] = C_RGB(buffer[i*3], buffer[i*3+1], buffer[i*3+2]);
		}
		free(buffer);

		currentFrame.data = (uint8_t*)frame;
		currentFrame.duration = static_cast<uint>(gif->gce.delay*10);
		return true;
	}
	return false;
}

bool GIFAnimatedSprite::newFrameReady(){
	uint cFrameTime = currentFrameTime;
	uint currentTime = millis();
	if(cFrameTime + currentFrame.duration < currentTime){
		return true;
	}
	return false;
}

void GIFAnimatedSprite::setScale(uint8_t scale){
	GIFAnimatedSprite::scale = scale;

}
