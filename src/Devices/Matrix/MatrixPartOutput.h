#ifndef CIRCUITOS_MATRIXPARTOUTPUT_H
#define CIRCUITOS_MATRIXPARTOUTPUT_H

#include <Arduino.h>
#include "MatrixOutputBuffer.h"

class MatrixPartOutput : public MatrixOutput {
public:
	MatrixPartOutput(MatrixOutputBuffer* output, int16_t width, int16_t height);

	void init() override;
	void push(const MatrixPixelData& data) override;

	void setBrightness(uint8_t brightness) override;

protected:
	virtual std::pair<uint16_t, uint16_t> map(uint16_t x, uint16_t y) = 0;

private:
	MatrixOutputBuffer* output;

};


#endif //CIRCUITOS_MATRIXPARTOUTPUT_H
