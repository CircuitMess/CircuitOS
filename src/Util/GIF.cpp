#include "GIF.h"

GIF::GIF(){ }

GIF::GIF(fs::File file){
	if(!file) return;
	file.seek(0);
	gif = CircuitOS::gd_open_gif(file);
	data = std::shared_ptr<Pixel>(new Pixel[getWidth()*getHeight()], std::default_delete<Pixel[]>());
}

GIF::~GIF(){
	if(gif == nullptr) return;
	gd_close_gif(gif);
}

GIF::operator bool() const{
	return gif != nullptr;
}

GIF& GIF::operator=(const GIF& other){
	if(this == &other) return *this;

	if(gif){
		gd_close_gif(gif);
		gif = nullptr;
	}

	loopMode = other.loopMode;
	loopCount = 0;

	File file = other.gif->fd;
	file.seek(0);
	gif = CircuitOS::gd_open_gif(file);

	return *this;
}

bool GIF::nextFrame(){
	if(gif == nullptr) return false;

	if(gd_get_frame(gif) != 1){
		loopCount++;

		switch(loopMode){
			case Auto:
				if(gif->loop_count != 0 && loopCount == gif->loop_count) return false;
				else{
					gd_rewind(gif);
					gd_get_frame(gif);
				}
				break;
			case Single:
				return false;
			case Infinite:
				gd_rewind(gif);
				gd_get_frame(gif);
				break;
		}
	}

	return true;
}

GIF::Frame GIF::getFrame() const{
	if(gif == nullptr) return { };


	gd_render_frame(gif, reinterpret_cast<uint8_t*>(data.get()), false);

	return { getWidth(), getHeight(), (uint32_t) gif->gce.delay * 10, data };
}

uint32_t GIF::frameDuration() const{
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

uint32_t GIF::getLoopCount() const{
	return loopCount;
}

GIF::Frame::Frame(){ }

GIF::Frame::Frame(uint16_t width, uint16_t height, uint32_t duration, std::shared_ptr<Pixel> data) : width(width), height(height), duration(duration), data(data){ }

GIF::Frame::Frame(const GIF::Frame& other) : Frame(other.width, other.height, other.duration, other.data){
	*this = other;
}

GIF::Frame& GIF::Frame::operator=(const GIF::Frame& other){
	if(&other == this) return *this;

	width = other.width;
	height = other.height;
	duration = other.duration;

	data.reset();
	data = other.data;

	return *this;
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

const Pixel* GIF::Frame::getData() const{
	return data.get();
}
