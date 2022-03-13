#ifndef CIRCUITOS_GIF_H
#define CIRCUITOS_GIF_H

#include <Arduino.h>
#include <FS.h>
#include "gifdec.h"

class GIF {
public:
	GIF();
	GIF(fs::File file);
	virtual ~GIF();

	operator bool() const;

	uint16_t getWidth() const;
	uint16_t getHeight() const;

	enum LoopMode { AUTO, SINGLE, INFINITE };
	LoopMode getLoopMode() const;
	void setLoopMode(LoopMode loopMode);

	struct Pixel { uint8_t r, g, b; };
	struct Frame {
	public:
		Frame();
		Frame(uint16_t width, uint16_t height, uint32_t duration, Pixel* data);
		Frame(const Frame& other);
		Frame& operator=(const Frame& other);
		uint16_t getWidth() const;
		uint16_t getHeight() const;
		uint32_t getDuration() const;
		const Pixel* getData() const;
		virtual ~Frame();

	private:
		uint16_t width = 0, height = 0;
		uint32_t duration = 0; // [ms]
		Pixel* data = nullptr;

	};

	void reset();
	bool nextFrame();
	Frame getFrame();
	uint32_t frameDuration();

private:
	gd_GIF* gif = nullptr;

	LoopMode loopMode = AUTO;
	uint32_t loopCount = 0;

};


#endif //CIRCUITOS_GIF_H
