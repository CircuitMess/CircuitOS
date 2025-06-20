#include "MatrixOutputBuffer.h"

MatrixOutputBuffer::MatrixOutputBuffer(MatrixOutput* output) : MatrixOutput(output->getWidth(), output->getHeight()), output(output),
															   data(output->getWidth(), output->getHeight()){

}

MatrixOutputBuffer::MatrixOutputBuffer(uint16_t width, uint16_t height) : MatrixOutput(width, height), data(width, height){

}

void MatrixOutputBuffer::setOutput(MatrixOutput* output){
	this->output = output;
}

void MatrixOutputBuffer::init(){

}

void MatrixOutputBuffer::push(const MatrixPixelData& data){
	this->data = data;

	if(output == nullptr) return;
	output->push(data);
}

void MatrixOutputBuffer::_push(){
	if(output == nullptr) return;
	output->push(data);
}

void MatrixOutputBuffer::setBrightness(uint8_t brightness){
	MatrixOutput::setBrightness(brightness);

	if(output == nullptr) return;
	output->setBrightness(brightness);
}

const MatrixPixelData& MatrixOutputBuffer::getData(){
	return data;
}
