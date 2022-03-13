#ifndef CIRCUITOS_MATRIXOUTPUT_H
#define CIRCUITOS_MATRIXOUTPUT_H

#include <Arduino.h>
#include "MatrixPixel.h"

class MatrixOutput {
public:

	MatrixOutput(uint16_t width, uint16_t height);

	virtual void init() = 0;
	virtual void push(const MatrixPixelData& data) = 0;

	uint16_t getWidth() const;
	uint16_t getHeight() const;
	virtual uint8_t getBrightness() const;
	virtual void setBrightness(uint8_t brightness);

private:
	uint16_t width, height;
	uint8_t brightness = 255;

};


#endif //CIRCUITOS_MATRIXOUTPUT_H
