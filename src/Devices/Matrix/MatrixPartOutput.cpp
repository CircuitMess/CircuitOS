#include "MatrixPartOutput.h"

MatrixPartOutput::MatrixPartOutput(MatrixOutputBuffer* output, int16_t width, int16_t height) : MatrixOutput(width, height), output(output){

}

void MatrixPartOutput::init(){
	output->init();
}

void IRAM_ATTR MatrixPartOutput::push(const MatrixPixelData& data){
	MatrixPixelData whole = output->getData();

	for(int x = 0; x < getWidth(); x++){
		for(int y = 0; y < getHeight(); y++){
			auto pixel = data.get(x, y);
			auto target = map(x, y);
			whole.set(target.first, target.second, pixel);
		}
	}

	output->push(whole);
}

void MatrixPartOutput::setBrightness(uint8_t brightness){
	MatrixOutput::setBrightness(brightness);
	output->setBrightness(brightness);
}
