#ifndef CIRCUITOS_GIF_H
#define CIRCUITOS_GIF_H

#include <Arduino.h>
#include <FS.h>
#include "gifdec.h"
#include "../Display/Color.h"

class GIF {
public:
	GIF();
	GIF(fs::File file);
	virtual ~GIF();

	operator bool() const;
	GIF& operator=(const GIF& other);

	uint16_t getWidth() const;
	uint16_t getHeight() const;

	enum LoopMode { Auto, Single, Infinite };
	LoopMode getLoopMode() const;
	void setLoopMode(LoopMode loopMode);

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
	Frame getFrame() const;
	uint32_t frameDuration() const;
	uint32_t getLoopCount() const;

private:
	CircuitOS::gd_GIF* gif = nullptr;

	LoopMode loopMode = Auto;
	uint32_t loopCount = 0;

};


#endif //CIRCUITOS_GIF_H
