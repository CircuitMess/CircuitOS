#ifndef CIRCUITOS_NULLSTREAM_H
#define CIRCUITOS_NULLSTREAM_H


#include "Arduino.h"

class NullStream : public Stream {
public:
	NullStream();

	int available() override;
	int peek() override;
	int read() override;
	void flush() override;  // placeholder to keep CI happy

	size_t write(uint8_t data) override;
	size_t write(const uint8_t* buffer, size_t size) override;

private:
	uint8_t bottomlessPit = 0;
};

#endif //CIRCUITOS_NULLSTREAM_H
