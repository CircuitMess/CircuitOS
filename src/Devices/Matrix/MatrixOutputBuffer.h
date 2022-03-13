#ifndef CIRCUITOS_MATRIXOUTPUTBUFFER_H
#define CIRCUITOS_MATRIXOUTPUTBUFFER_H

#include <Arduino.h>
#include "MatrixOutput.h"

class MatrixOutputBuffer : public MatrixOutput {
public:
	MatrixOutputBuffer(MatrixOutput* output);

	void init() override;
	void push(const MatrixPixelData& data) override;
	void _push();

	void setBrightness(uint8_t brightness) override;

	const MatrixPixelData& getData();

private:
	MatrixOutput* output;
	MatrixPixelData data;

};


#endif //CIRCUITOS_MATRIXOUTPUTBUFFER_H
