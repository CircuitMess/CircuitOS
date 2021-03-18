#include "AnimatedSprite.h"
#include "gifdec.h"

AnimatedSprite::AnimatedSprite(Sprite* canvas, fs::File file, bool loop) : canvas(canvas), file(file), loop(loop){
	if(!file){
		Serial.printf("AnimatedGif file %s not open\n", file.name());
		return;
	}

	file.seek(0);

	Header header;
	file.read(reinterpret_cast<uint8_t*>(&header), sizeof(Header));

	width = header.width;
	height = header.height;
	noFrames = header.noFrames;
	flags = header.flags;

	if(flags){
		table = new Table(file);
	}

	gifFrame.data = static_cast<uint8_t*>(malloc(width * height * (flags ? 1 : 2)));

	dataStart = file.position();
	reset();
}

AnimatedSprite::Table::Table(fs::File& file){
	file.read(&noColors, sizeof(noColors));
	colors = static_cast<Color*>(malloc(sizeof(Color) * noColors));
	file.read(reinterpret_cast<uint8_t*>(colors), sizeof(Color) * noColors);
}

AnimatedSprite::Table::~Table(){
	delete colors;
}

Color AnimatedSprite::Table::getColor(uint8_t i) const {
	if(colors == nullptr || i >= noColors) return 0;
	return colors[i];
}

AnimatedSprite::~AnimatedSprite(){
	delete table;
	delete gifFrame.data;
}

void AnimatedSprite::push(){
	if(flags){
		for(int i = 0; i < width * height; i++){
			Color color = table->getColor(gifFrame.data[i]);
			if(color == TFT_TRANSPARENT) continue;

			int _y = i / width;
			int _x = i - _y * width;

			canvas->drawPixel(x + _x, y + _y, color);
		}
	}else{
		canvas->drawIcon(reinterpret_cast<const unsigned short*>(gifFrame.data), x, y, width, height, 1, TFT_TRANSPARENT);
	}

}

void AnimatedSprite::reset(){
	file.seek(dataStart);
	currentFrameTime = 0;
	currentFrame = 0;
	alerted = false;
	done = false;
}

void AnimatedSprite::setLoopDoneCallback(void (*callback)()){
	loopDoneCallback = callback;
}

bool AnimatedSprite::nextFrame(){
	if(done) return false;

	if(currentFrameTime == 0){
		file.read(reinterpret_cast<uint8_t*>(&gifFrame.duration), sizeof(gifFrame.duration));
		file.read(gifFrame.data, width * height * (flags ? 1 : 2));
		currentFrameTime = millis();
		return true;
	}

	bool newFrame = false;

	uint currentTime = millis();
	while(currentFrameTime + gifFrame.duration < currentTime){
		currentFrameTime += gifFrame.duration;
		currentFrame++;

		file.read(reinterpret_cast<uint8_t*>(&gifFrame.duration), sizeof(gifFrame.duration));
		file.read(gifFrame.data, width * height * (flags ? 1 : 2));

		newFrame = true;
		if(currentFrame == noFrames-1){
			done = true;
		}
	}

	return newFrame;
}

bool AnimatedSprite::checkFrame(){
	if(currentFrameTime == 0) return true;
	if(done && alerted) return false; // if on last frame, so user can push after it ends, triggering the callback

	if(currentFrameTime + gifFrame.duration < millis()){
		if(done && !alerted){
			alerted = true;

			// Order of callbacks is important in case the AnimatedSprite gets deleted in it.

			if(loop){
				reset();

				if(loopDoneCallback != nullptr){
					loopDoneCallback();
				}

				return true;
			}

			if(loopDoneCallback != nullptr){
				loopDoneCallback();
			}

			return false;
		}

		return true;
	}

	return false;
}

void AnimatedSprite::setX(int16_t x){
	AnimatedSprite::x = x;
}

void AnimatedSprite::setY(int16_t y){
	AnimatedSprite::y = y;
}

void AnimatedSprite::setXY(int16_t x, int16_t y){
	AnimatedSprite::x = x;
	AnimatedSprite::y = y;
}

uint16_t AnimatedSprite::getWidth() const{
	return width;
}

uint16_t AnimatedSprite::getHeight() const{
	return height;
}
