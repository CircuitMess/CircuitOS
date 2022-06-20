#ifndef JAYD_LIBRARY_FSBUFFER_H
#define JAYD_LIBRARY_FSBUFFER_H

#include <Arduino.h>
#include <FS.h>

class FSBuffer {
public:
	FSBuffer(File file, const size_t size);
	virtual ~FSBuffer();

	size_t available();
	bool moveRead(size_t amount);
	bool refill();
	void clear();

	const uint8_t* data();
	File getFile() const;

private:
	fs::File file;
	const size_t size;
	size_t bytesFilled = 0;

	uint8_t* buffer = nullptr;
	size_t cursor = 0;

};


#endif //JAYD_LIBRARY_FSBUFFER_H
