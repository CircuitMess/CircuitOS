#ifndef CIRCUITOS_GIFANIMATEDSPRITE_H
#define CIRCUITOS_GIFANIMATEDSPRITE_H

#include <vector>
#include "../Loop/LoopListener.h"
#include "Sprite.h"
#include <FS.h>
#include <experimental/functional>
#include "../Util/GIF.h"

class GIFAnimatedSprite : private LoopListener {
public:
	GIFAnimatedSprite(Sprite* parentSprite, const fs::File& gifFile);
	virtual ~GIFAnimatedSprite();
	void loop(uint micros) override;

	void start();
	void stop();

	/**
	 * @brief Pushes the current GIF frame onto the parentSprite defined in the constructor,
	 * 		  on the position selected by the setter/getters
	 */
	void push() const;

	/**
	 * @brief Pushes the current GIF frame onto the sprite and position provided, overriding the previously set parentSprite and position.
	 * @param sprite Sprite to be pushed on
	 * @param x, y Relative position on the sprite.
	 */
	void push(Sprite* sprite, int x, int y) const;

	void reset();

	int getX() const;
	void setX(int x);
	int getY() const;
	void setY(int y);
	void setXY(int x, int y);
	uint16_t getWidth() const;
	uint16_t getHeight() const;

	GIF::LoopMode getLoopMode() const;
	void setLoopMode(GIF::LoopMode loopMode);
	uint32_t getLoopCount() const;

	void setLoopDoneCallback(std::function<void()> loopDoneCallback);
	void setScale(uint8_t scale);

private:
	GIF gif;
	Sprite* parentSprite = nullptr;
	int16_t x = 0, y = 0;

	uint32_t frameCounter = 0;
	uint32_t loopCount = 0;

	uint8_t scale = 1;

	std::function<void()> loopDoneCallback;
};


#endif //CIRCUITOS_GIFANIMATEDSPRITE_H
