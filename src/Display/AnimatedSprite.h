#ifndef CIRCUITOS_ANIMATEDSPRITE_H
#define CIRCUITOS_ANIMATEDSPRITE_H


#include <vector>
#include "../Loop/LoopListener.h"
#include "Sprite.h"
#include <FS.h>

class gd_GIF;

class AnimatedSprite {
public:
	AnimatedSprite(Sprite* parentSprite, fs::File gifFile);
	virtual ~AnimatedSprite();

	int getX() const;
	void setX(int x);
	int getY() const;
	void setY(int y);
	void setXY(int x, int y);

	void push();
	void reset();
	void setLoopDoneCallback(void (*callback)());

private:
	Sprite* parentSprite = nullptr;
	int x = 0, y = 0;
	uint16_t width, height;

	gd_GIF* gif;
	fs::File gifFile;
	uint32_t currentFrameTime = 0;

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

	void (*loopDoneCallback)() = nullptr;
	bool alerted = false;
};


#endif //CIRCUITOS_ANIMATEDSPRITE_H
