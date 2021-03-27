#ifndef JAYD_LIBRARY_LAZYDATABUFFER_H
#define JAYD_LIBRARY_LAZYDATABUFFER_H

#include <Arduino.h>

class LazyDataBuffer {
public:
	LazyDataBuffer(const size_t size);
	virtual ~LazyDataBuffer();

	size_t readAvailable();
	bool readMove(size_t amount);
	const uint8_t* readData();

	size_t writeAvailable();
	bool writeMove(size_t amount);
	uint8_t* writeData();

	size_t potentialWriteAvailable();

	void clear();
	void relocate();

private:
	const size_t size;

	uint8_t* buffer = nullptr;
	size_t readCursor = 0;
	size_t writeCursor = 0;
};


#endif //JAYD_LIBRARY_LAZYDATABUFFER_H
