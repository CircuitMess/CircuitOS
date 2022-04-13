#include "MatrixOutputBuffer.h"

MatrixOutputBuffer::MatrixOutputBuffer(MatrixOutput* output) : MatrixOutput(output->getWidth(), output->getHeight()), output(output),
															   data(output->getWidth(), output->getHeight()){

}

void MatrixOutputBuffer::init(){

}

void MatrixOutputBuffer::push(const MatrixPixelData& data){
	this->data = data;
	output->push(data);
}

void MatrixOutputBuffer::_push(){
	output->push(data);
}

void MatrixOutputBuffer::setBrightness(uint8_t brightness){
	MatrixOutput::setBrightness(brightness);
	output->setBrightness(brightness);
}

const MatrixPixelData& MatrixOutputBuffer::getData(){
	return data;
}
