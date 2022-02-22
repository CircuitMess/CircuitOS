#ifndef CIRCUITOS_MATRIXOUTPUT_H
#define CIRCUITOS_MATRIXOUTPUT_H

#include <Arduino.h>

class MatrixOutput {
public:
	MatrixOutput(uint width, uint height) : width(width), height(height){};
	virtual void init() = 0;
	virtual void push(void* data) = 0;

	void setBrightness(uint8_t brightness){
		MatrixOutput::brightness = brightness;
	}
	uint8_t getBrightness() const{
		return brightness;
	}

protected:
	uint width, height;
	uint8_t brightness = 255;
};


#endif //CIRCUITOS_MATRIXOUTPUT_H
