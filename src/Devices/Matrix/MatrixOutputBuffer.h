#ifndef CIRCUITOS_MATRIXOUTPUTBUFFER_H
#define CIRCUITOS_MATRIXOUTPUTBUFFER_H

#include <Arduino.h>
#include "MatrixOutput.h"

class MatrixOutputBuffer : public MatrixOutput {
public:
	MatrixOutputBuffer(MatrixOutput* output);
	MatrixOutputBuffer(uint16_t width, uint16_t height);

	void setOutput(MatrixOutput* output); // For use with non-output constructor

	void init() override;
	void push(const MatrixPixelData& data) override;
	void _push();

	void setBrightness(uint8_t brightness) override;

	const MatrixPixelData& getData();

private:
	MatrixOutput* output = nullptr;
	MatrixPixelData data;

};


#endif //CIRCUITOS_MATRIXOUTPUTBUFFER_H
