#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(Sprite* canvas, fs::File file, bool compressed) : canvas(canvas), file(file), compressed(compressed){
	if(!file){
		Serial.printf("AnimatedGif file %s not open\n", file.name());
		return;
	}
	file.seek(0);
	Header header;
	if(file.read(reinterpret_cast<uint8_t*>(&header), sizeof(Header)) != sizeof(Header)){
		Serial.println("Failed reading G565 header");
		return;
	}
	width = header.width;
	height = header.height;
	noFrames = header.noFrames;
	flags = header.flags;

	if(flags){
		table = new Table(file);
	}
#ifdef CONFIG_SPIRAM_SUPPORT
	if(psramFound()){
		gifFrame.data = static_cast<uint8_t*>(ps_malloc(width * height * (flags ? 1 : 2)));
	}else{
		gifFrame.data = static_cast<uint8_t *>(malloc(width * height * (flags ? 1 : 2)));
	}
#else
	gifFrame.data = static_cast<uint8_t *>(malloc(width * height * (flags ? 1 : 2)));
#endif

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

uint8_t AnimatedSprite::Table::getNoColors() const{
	return noColors;
}

AnimatedSprite::~AnimatedSprite(){

	delete table;
	delete gifFrame.data;
	file.close();

}

void AnimatedSprite::push(){
	if(flags){
		for(int i = 0; i < width * height; i++){
			Color color = table->getColor(gifFrame.data[i]);
			if(swapBytes){
				color = color << 8 | color >> 8;
			}
			if(color == maskingColor) continue;

			int _y = i / width;
			int _x = i - _y * width;

			canvas->drawPixel(x + _x, y + _y, color);
		}
	}else{
		canvas->drawIcon(reinterpret_cast<const unsigned short*>(gifFrame.data), x, y, width, height, 1, maskingColor);
	}

}

void AnimatedSprite::reset(){
	if(compressed){
		file.seek(0);
		Header header;
		file.read(reinterpret_cast<uint8_t*>(&header), sizeof(Header));
	}else{
		file.seek(dataStart);
	}
	currentFrameTime = 0;
	currentFrame = 0;
	alerted = false;
	onLastFrame = false;
	playing = true;
}

void AnimatedSprite::setLoopDoneCallback(void (*callback)()){
	loopDoneCallback = callback;
}

bool AnimatedSprite::nextFrame(){
	if(!playing) return false;
	if(onLastFrame) return false;

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

		if(currentFrame == noFrames){
			currentFrame = 0;
			file.seek(dataStart);
		}

		file.read(reinterpret_cast<uint8_t*>(&gifFrame.duration), sizeof(gifFrame.duration));
		file.read(gifFrame.data, width * height * (flags ? 1 : 2));

		newFrame = true;
		if(currentFrame == noFrames-1){
			onLastFrame = true;
			if(!loop) break;
		}
	}

	return newFrame;
}

bool AnimatedSprite::checkFrame(){
	if(currentFrameTime == 0) return true;
	if(onLastFrame && alerted) return false;

	if(currentFrameTime + gifFrame.duration < millis()){
		if(onLastFrame && !alerted){
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

void AnimatedSprite::setLoop(bool loop){
	AnimatedSprite::loop = loop;
}

void AnimatedSprite::setMaskingColor(Color maskingColor){
	AnimatedSprite::maskingColor = maskingColor;
}

void AnimatedSprite::setSwapBytes(bool swapBytes){
	AnimatedSprite::swapBytes = swapBytes;
}

void AnimatedSprite::start(){
	playing = true;
	currentFrameTime = millis();
}

void AnimatedSprite::stop(){
	playing = false;
}
