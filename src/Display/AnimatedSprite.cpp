#include "AnimatedSprite.h"
#include "PGMFile.h"
#include "gifdec.h"

AnimatedSprite::AnimatedSprite(Sprite* parentSprite, uint8_t* gifData, size_t gifSize) : parentSprite(parentSprite){
	PGMFile file(gifData, gifSize);
	gd_GIF* gif = gd_open_gif(&file);
	if(gif == nullptr){
		Serial.println("Failed opening gif");
		return;
	}

	width = gif->width;
	height = gif->height;

	while (gd_get_frame(gif) == 1) {
		uint8_t *buffer = (uint8_t*) malloc(width * height * 3);
		//render 24-bit color frame into buffer
		gd_render_frame(gif, buffer, false);

		uint16_t* frame = static_cast<uint16_t*>(malloc(width * height * sizeof(uint16_t)));
		for(int i = 0; i < width * height; i++){
			frame[i] = C_RGB(buffer[i*3], buffer[i*3+1], buffer[i*3+2]);
		}

		free(buffer);

		frames.push_back({ (uint8_t*) frame, static_cast<uint>(gif->gce.delay*10) });
	}

	gd_close_gif(gif);
}

AnimatedSprite::~AnimatedSprite(){
	for(const Frame& frame : frames){
		free(frame.data);
	}
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
		parentSprite->drawIcon(reinterpret_cast<const unsigned short*>(frames[currentFrame].data), x, y, width, height, 1, TFT_TRANSPARENT);
		currentFrameTime = millis();
		return;
	}

	uint cFrameTime = currentFrameTime;
	uint currentTime = millis();
	while(cFrameTime + frames[currentFrame].duration < currentTime){
		cFrameTime += frames[currentFrame].duration;
		currentFrame = (currentFrame + 1) % frames.size();
		currentFrameTime = currentTime;

		if(currentFrame == 0){
			if(loopDoneCallback != nullptr && !alerted){
				loopDoneCallback();
				alerted = true;
			}
		}else{
			alerted = false;
		}
	}

	parentSprite->drawIcon(reinterpret_cast<const unsigned short*>(frames[currentFrame].data), x, y, width, height, 1, TFT_TRANSPARENT);
}

void AnimatedSprite::reset(){
	currentFrame = 0;
	currentFrameTime = 0;
}

void AnimatedSprite::setLoopDoneCallback(void (*callback)()){
	loopDoneCallback = callback;
}
