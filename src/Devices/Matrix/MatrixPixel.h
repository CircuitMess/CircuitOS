#ifndef CIRCUITOS_MATRIXPIXEL_H
#define CIRCUITOS_MATRIXPIXEL_H

#include <Arduino.h>
#include <vector>
#include "../../Util/GIF.h"

struct MatrixPixel {
	uint8_t r, g, b, i;
	static const MatrixPixel Red;
	static const MatrixPixel Green;
	static const MatrixPixel Blue;
	static const MatrixPixel Magenta;
	static const MatrixPixel Cyan;
	static const MatrixPixel Yellow;
	static const MatrixPixel White;
	static const MatrixPixel Black;
	static const MatrixPixel Off;
};

bool operator==(const MatrixPixel& a, const MatrixPixel& b);
bool operator!=(const MatrixPixel& a, const MatrixPixel& b);

class MatrixPixelData {
public:
	MatrixPixelData(uint16_t width, uint16_t height);
	MatrixPixelData(const GIF::Frame& gifFrame);
	MatrixPixelData(const MatrixPixelData& other);
	MatrixPixelData& operator=(const MatrixPixelData& other);

	uint16_t getWidth() const;
	uint16_t getHeight() const;

	void set(uint16_t x, uint16_t y, const MatrixPixel& pixel);
	MatrixPixel get(uint16_t x, uint16_t y) const;

	void clear(const MatrixPixel& color = { 0, 0, 0, 0 });

	class Column {
	public:
		Column(MatrixPixelData& parent, uint16_t x);
		MatrixPixel& operator[](uint16_t y) const;

	private:
		MatrixPixelData& parent;
		uint16_t x;
	};

	Column operator[](uint16_t x);

private:
	uint16_t width, height;
	std::vector<std::vector<MatrixPixel>> data;

};

#endif //CIRCUITOS_MATRIXPIXEL_H
