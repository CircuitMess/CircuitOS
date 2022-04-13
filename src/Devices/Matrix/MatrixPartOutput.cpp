#include "MatrixPartOutput.h"

MatrixPartOutput::MatrixPartOutput(MatrixOutputBuffer* output, int16_t width, int16_t height) : MatrixOutput(width, height), output(output){

}

void MatrixPartOutput::init(){

}

void IRAM_ATTR MatrixPartOutput::push(const MatrixPixelData& data){
	MatrixPixelData whole = output->getData();

	for(int x = 0; x < getWidth(); x++){
		for(int y = 0; y < getHeight(); y++){
			auto pixel = data.get(x, y);
			auto target = map(x, y);
			pixel.i = pixel.i * getBrightness() / 255;
			whole.set(target.first, target.second, pixel);
		}
	}

	output->push(whole);
}