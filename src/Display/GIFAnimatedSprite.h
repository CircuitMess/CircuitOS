#ifndef CIRCUITOS_GIFANIMATEDSPRITE_H
#define CIRCUITOS_GIFANIMATEDSPRITE_H


#include <vector>
#include "../Loop/LoopListener.h"
#include "Sprite.h"
#include <FS.h>
#include <experimental/functional>

class gd_GIF;

enum class LoopMode { Auto, Single, Infinite };

class GIFAnimatedSprite {
public:
	GIFAnimatedSprite(Sprite* parentSprite, fs::File gifFile);
	virtual ~GIFAnimatedSprite();

	int getX() const;
	void setX(int x);
	int getY() const;
	void setY(int y);
	void setXY(int x, int y);

	void push();
	void reset();

	LoopMode getLoopMode() const;
	void setLoopMode(LoopMode loopMode);
	void setLoopDoneCallback(std::function<void()> loopDoneCallback);

	bool newFrameReady();
	void setScale(uint8_t scale);

private:
	Sprite* parentSprite = nullptr;
	int x = 0, y = 0;
	uint16_t width, height;

	gd_GIF* gif;
	fs::File gifFile;
	uint32_t currentFrameTime = 0;
	uint8_t scale=1;

	struct Frame {
		uint8_t* data = nullptr;
		uint32_t duration = 0;
	};
	Frame currentFrame;

	/**
	 * @brief Function to load the next frame of the GIF, if available.
	 *
	 * @return true New frame is loaded successfully.
	 * @return false Reached the end of GIF, no more frames available.
	 */
	bool nextFrame();

	LoopMode loopMode = LoopMode::Single;
	uint32_t loopCount = 0;
	std::function<void()> loopDoneCallback;
	bool alerted = false;
};



#endif //CIRCUITOS_GIFANIMATEDSPRITE_H
