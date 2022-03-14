#include "MatrixPixel.h"

MatrixPixelData::MatrixPixelData(uint16_t width, uint16_t height) : width(width), height(height){
	data.resize(width);
	for(int x = 0; x < width; x++){
		data[x].resize(height);
	}
}

MatrixPixelData::MatrixPixelData(const GIF::Frame& frame) : MatrixPixelData(frame.getWidth(), frame.getHeight()){
	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			GIF::Pixel pix = frame.getData()[y * frame.getWidth() + x];
			data[x][y] = { pix.r, pix.g, pix.b, 255 };
		}
	}
}

MatrixPixelData::MatrixPixelData(const MatrixPixelData& other){
	*this = other;
}

MatrixPixelData& IRAM_ATTR MatrixPixelData::operator=(const MatrixPixelData& other){
	if(&other == this) return *this;

	width = other.width;
	height = other.height;

	data.resize(width);
	for(int x = 0; x < width; x++){
		data[x].resize(height);
		memcpy(data[x].data(), other.data[x].data(), height * sizeof(MatrixPixel));
	}

	return *this;
}

void MatrixPixelData::set(uint16_t x, uint16_t y, const MatrixPixel& pixel){
	if(x >= width || y >= height) return;
	data[x][y] = pixel;
}

MatrixPixel MatrixPixelData::get(uint16_t x, uint16_t y) const{
	if(x >= width || y >= height) return { };
	return data[x][y];
}

void MatrixPixelData::clear(const MatrixPixel& color){
	for(int x = 0; x < width; x++){
		data[x] = std::vector<MatrixPixel>(height, color);
	}
}

uint16_t MatrixPixelData::getWidth() const{
	return width;
}

uint16_t MatrixPixelData::getHeight() const{
	return height;
}

MatrixPixelData::Column MatrixPixelData::operator[](uint16_t x){
	return Column(*this, x);
}

MatrixPixelData::Column::Column(MatrixPixelData& parent, uint16_t x) : parent(parent), x(x){ }

MatrixPixel& MatrixPixelData::Column::operator[](uint16_t y) const{
	if(x >= parent.width || y >= parent.height) throw std::exception();
	return parent.data[x][y];
}