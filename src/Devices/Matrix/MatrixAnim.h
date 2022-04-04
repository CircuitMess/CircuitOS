#ifndef CIRCUITOS_MATRIXANIM_H
#define CIRCUITOS_MATRIXANIM_H

#include <Arduino.h>
#include "MatrixPixel.h"

class Matrix;

class MatrixAnim {
public:
	MatrixAnim(Matrix* matrix);
	virtual ~MatrixAnim();

	void start();
	void stop();
	virtual void reset() = 0;

	bool isStarted();

	void setX(int32_t x);
	void setY(int32_t y);
	void setWidth(uint32_t width);
	void setHeight(uint32_t height);

protected:
	void drawPixel(uint16_t x, uint16_t y, const MatrixPixel& color);
	void drawPixel(uint16_t i, const MatrixPixel& color);
	void drawChar(int32_t x, int32_t y, unsigned char c, const MatrixPixel& color = { 255, 255, 255, 255 });
	void drawString(int32_t x, int32_t y, const String &text, const MatrixPixel& color = { 255, 255, 255, 255 });
	void drawBitmap(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t* data, const MatrixPixel& color = { 255, 255, 255, 255 });
	void drawBitmap(uint16_t x, uint16_t y, const MatrixPixelData& data);
	void push();
	void clear();

	virtual void onStart() = 0;
	virtual void onStop() = 0;

private:
	Matrix* matrix;
	bool started = false;

	int32_t _x = 0, _y = 0;
	uint32_t width, height;
};

#endif