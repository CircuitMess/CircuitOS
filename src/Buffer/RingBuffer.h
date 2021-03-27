#ifndef CIRCUITOS_RINGBUFFER_H
#define CIRCUITOS_RINGBUFFER_H

#include <Arduino.h>

class RingBuffer {
public:
	RingBuffer(size_t size);
	virtual ~RingBuffer();

	size_t writeAvailable();
	size_t readAvailable();

	size_t read(uint8_t* destination, size_t n);
	size_t write(uint8_t* source, size_t n);

	void clear();

private:
	size_t size;

	size_t beginning = 0;
	size_t end = 0;

	uint8_t* buffer;
};


#endif //CIRCUITOS_RINGBUFFER_H
