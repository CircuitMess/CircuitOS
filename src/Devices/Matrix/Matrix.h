#ifndef CIRCUITOS_MATRIX_H
#define CIRCUITOS_MATRIX_H

#include <Arduino.h>
#include <unordered_set>
#include "MatrixOutput.h"
#include "MatrixAnim.h"

class Matrix {
friend MatrixAnim;
public:
	Matrix(MatrixOutput& output);
	void begin();
	void clear(MatrixPixel color = MatrixPixel::Off);
	void push();

	void setRotation(uint8_t rotation);
	uint8_t getRotation() const;

	/**
	 * Set global brightness.
	 * @param brightness 0-255
	 */
	void setBrightness(uint8_t brightness);
	uint8_t getBrightness() const;

	enum Font { BIG, SMALL };

	/**
	 * Set the drawChar and drawString font. BIG is 5x7, SMALL is 3x5
	 * @param font BIG or SMALL
	 */
	void setFont(Font font);
	Font getFont() const;

	void drawPixel(uint16_t x, uint16_t y, const MatrixPixel& color);
	void drawPixel(uint16_t i, const MatrixPixel& color);

	void drawChar(int32_t x, int32_t y, unsigned char c, const MatrixPixel& color = { 255, 255, 255, 255 });
	void drawString(int32_t x, int32_t y, const String &text, const MatrixPixel& color = { 255, 255, 255, 255 });

	void drawBitmap(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t* data, const MatrixPixel& color = { 255, 255, 255, 255 });
	void drawBitmap(uint16_t x, uint16_t y, const MatrixPixelData& data);

	void startAnimation(MatrixAnim* animation);
	void stopAnimations();
	std::unordered_set<MatrixAnim*> getAnimations();

	const uint16_t getWidth() const;
	const uint16_t getHeight() const;

private:
	MatrixOutput& output;
	MatrixPixelData data;

	const uint16_t width, height;

	uint8_t rotation = 0;
	Font font = BIG;

	std::unordered_set<MatrixAnim*> animations;
	void addAnim(MatrixAnim* anim);
	void removeAnim(MatrixAnim* anim);

};

#endif