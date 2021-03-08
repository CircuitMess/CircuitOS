#include "AnimatedSprite.h"
#include "gifdec.h"

AnimatedSprite::AnimatedSprite(Sprite* parentSprite, fs::File _gifFile) : parentSprite(parentSprite), gifFile(_gifFile){
	gif = gd_open_gif(&gifFile);
	if(gif == nullptr){
		Serial.println("Failed opening gif");
		return;
	}

	width = gif->width;
	height = gif->height;

	if(!nextFrame()) return;

}

AnimatedSprite::~AnimatedSprite(){
	gd_close_gif(gif);
}

int AnimatedSprite::getX() const{
	return x;
}

void AnimatedSprite::setX(int x){
	AnimatedSprite::x = x;
}

int AnimatedSprite::getY() const{
	return y;
}

void AnimatedSprite::setY(int y){
	AnimatedSprite::y = y;
}

void AnimatedSprite::setXY(int x, int y){
	AnimatedSprite::x = x;
	AnimatedSprite::y = y;
}

void AnimatedSprite::push(){
	if(currentFrameTime == 0){
		parentSprite->drawIcon(reinterpret_cast<const unsigned short*>(currentFrame.data), x, y, width, height, 1, TFT_TRANSPARENT);
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
	parentSprite->drawIcon(reinterpret_cast<const unsigned short*>(currentFrame.data), x, y, width, height, 1, TFT_TRANSPARENT);
}

void AnimatedSprite::reset(){
	gd_rewind(gif);
	if(!nextFrame()) return;
	currentFrameTime = 0;
	alerted=false;
}

void AnimatedSprite::setLoopDoneCallback(void (*callback)()){
	loopDoneCallback = callback;
}

bool AnimatedSprite::nextFrame(){
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