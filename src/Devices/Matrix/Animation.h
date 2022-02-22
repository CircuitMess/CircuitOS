#ifndef SPENCER_ANIMATION_H
#define SPENCER_ANIMATION_H

#include <Arduino.h>
#include <vector>
#include <FS.h>
#include <FSImpl.h>


/*!
	@brief Struct to abstract 24-bit color values.
*/
struct RGBpixel{
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

/*!
	@brief Each frame is consisted of a 24-bit color depth array (length = w*h) and its duration in ms.
*/
struct AnimationFrame
{
	uint8_t *data;
	uint duration;
};

class Animation
{
public:
	Animation(fs::FileImpl* file);
	Animation(fs::File* file);
	~Animation();
	void rewind();
	AnimationFrame* getNextFrame();
	uint16_t getWidth();
	uint16_t getHeight();
	uint32_t getLoopDuration();

private:
	std::vector<AnimationFrame> frames;
	uint currentFrame = 0;

	uint16_t width;
	uint16_t height;
	uint32_t totalDuration = 0;
	fs::File* file;
};



#endif