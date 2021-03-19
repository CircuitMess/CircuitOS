#ifndef CIRCUITOS_ANIMATEDSPRITE_H
#define CIRCUITOS_ANIMATEDSPRITE_H


#include <vector>
#include "../Loop/LoopListener.h"
#include "Sprite.h"
#include "../UI/CustomElement.h"
#include "../UI/SpriteElement.h"
#include <FS.h>

class AnimatedSprite {
public:
	AnimatedSprite(Sprite* canvas, fs::File file);
	virtual ~AnimatedSprite();

	void push();
	void reset();
	void setLoopDoneCallback(void (*callback)());

	/**
	 * Checks if it's time for a new frame, and if so, loads it. This will fire the LoopDone callback.
	 * The callback will be called after last frame is over.
	 * @return True of a new frame is ready, false otherwise.
	 */
	bool checkFrame();

	/**
	 * @brief Function to load the next frame of the GIF, if available.
	 *
	 * @return true New frame is loaded successfully.
	 * @return false Reached the end of GIF, no more frames available.
	 */
	bool nextFrame();

	void setX(int16_t x);
	void setY(int16_t y);
	void setXY(int16_t x, int16_t y);

	uint16_t getWidth() const;
	uint16_t getHeight() const;

	void setLoop(bool loop);
	void setMaskingColor(Color maskingColor);

private:
	Sprite* canvas;
	fs::File file;
	bool loop = false;
	Color maskingColor = TFT_TRANSPARENT;
	size_t dataStart;
	uint32_t currentFrameTime = 0;

	int16_t x = 0;
	int16_t y = 0;
	uint16_t width;
	uint16_t height;

	struct Header {
		uint16_t width;
		uint16_t height;
		uint16_t noFrames;
		uint8_t flags;
	} __attribute__((packed));

	class Table {
	public:
		explicit Table(fs::File& file);
		~Table();

		Color getColor(uint8_t i) const;
	private:
		uint8_t noColors;
		Color* colors;
	} *table = nullptr;

	struct Frame {
		uint8_t* data = nullptr;
		uint16_t duration = 0;
	} gifFrame;

	uint16_t noFrames = 0;
	uint16_t currentFrame = 0;
	uint8_t flags;

	bool done = false;
	void (*loopDoneCallback)() = nullptr;
	bool alerted = false;
};


#endif //CIRCUITOS_ANIMATEDSPRITE_H
