#ifndef CIRCUITOS_ANIMATEDSPRITE_H
#define CIRCUITOS_ANIMATEDSPRITE_H


#include <vector>
#include "../Loop/LoopListener.h"
#include "Sprite.h"

class AnimatedSprite {
public:
	AnimatedSprite(Sprite* parentSprite, uint8_t* gifData, size_t gifSize);
	virtual ~AnimatedSprite();

	int getX() const;
	void setX(int x);
	int getY() const;
	void setY(int y);
	void setXY(int x, int y);

	void push();
	void reset();

private:
	Sprite* parentSprite = nullptr;
	int x = 0, y = 0;
	uint16_t width, height;

	uint16_t currentFrame = 0;
	uint32_t currentFrameTime = 0;

	struct Frame {
		uint8_t* data;
		uint32_t duration;
	};
	std::vector<Frame> frames;
};


#endif //CIRCUITOS_ANIMATEDSPRITE_H
