#include "GIF.h"

GIF::GIF(){ }

GIF::GIF(fs::File file){
	gif = gd_open_gif(file);
}

GIF::~GIF(){
	if(gif == nullptr) return;
	gd_close_gif(gif);
}

GIF::operator bool() const{
	return gif != nullptr;
}

bool GIF::nextFrame(){
	if(gif == nullptr) return false;

	if(gd_get_frame(gif) != 1){
		loopCount++;

		switch(loopMode){
			case AUTO:
				if(gif->loop_count != 0 && loopCount == gif->loop_count) return false;
				else{
					gd_rewind(gif);
					gd_get_frame(gif);
				}
				break;
			case SINGLE:
				return false;
			case INFINITE:
				gd_rewind(gif);
				gd_get_frame(gif);
				break;
		}
	}

	return true;
}

GIF::Frame GIF::getFrame(){
	if(gif == nullptr) return { };

	Pixel* data = new Pixel[getWidth() * getHeight()];
	gd_render_frame(gif, reinterpret_cast<uint8_t*>(data), false);

	return { getWidth(), getHeight(), (uint32_t) gif->gce.delay * 10, data };
}

uint32_t GIF::frameDuration(){
	if(gif == nullptr) return 0;
	return gif->gce.delay * 10;
}

void GIF::reset(){
	if(gif == nullptr) return;
	gd_rewind(gif);
	loopCount = 0;
}

uint16_t GIF::getWidth() const{
	return gif->width;
}

uint16_t GIF::getHeight() const{
	return gif->height;
}

GIF::LoopMode GIF::getLoopMode() const{
	return loopMode;
}

void GIF::setLoopMode(GIF::LoopMode loopMode){
	GIF::loopMode = loopMode;
}

GIF::Frame::Frame(){ }

GIF::Frame::Frame(uint16_t width, uint16_t height, uint32_t duration, GIF::Pixel* data) : width(width), height(height), duration(duration), data(data){ }

GIF::Frame::Frame(const GIF::Frame& other) : Frame(other.width, other.height, other.duration, new Pixel[other.width * other.height]){
	*this = other;
}

GIF::Frame& GIF::Frame::operator=(const GIF::Frame& other){
	if(&other == this) return *this;

	width = other.width;
	height = other.height;
	duration = other.duration;

	delete data;
	data = new Pixel[width * height];
	memcpy(data, other.data, width * height * 3);

	return *this;
}

GIF::Frame::~Frame(){
	delete data;
}

uint16_t GIF::Frame::getWidth() const{
	return width;
}

uint16_t GIF::Frame::getHeight() const{
	return height;
}

uint32_t GIF::Frame::getDuration() const{
	return duration;
}

const GIF::Pixel* GIF::Frame::getData() const{
	return data;
}
