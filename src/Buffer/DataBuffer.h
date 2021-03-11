#ifndef JAYD_LIBRARY_DATABUFFER_H
#define JAYD_LIBRARY_DATABUFFER_H

#include <Arduino.h>

class DataBuffer {
public:
	DataBuffer(const size_t size);
	virtual ~DataBuffer();

	size_t readAvailable();
	bool readMove(size_t amount);
	const uint8_t* readData();

	size_t writeAvailable();
	bool writeMove(size_t amount);
	uint8_t* writeData();

	void clear();

private:
	const size_t size;

	uint8_t* buffer = nullptr;
	size_t readCursor = 0;
	size_t writeCursor = 0;
};


#endif //JAYD_LIBRARY_DATABUFFER_H
