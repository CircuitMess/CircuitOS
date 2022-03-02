#ifndef SPENCER_LEDMATRIX_H
#define SPENCER_LEDMATRIX_H

#include <Arduino.h>
#include "Animation.h"
#include <Loop/LoopListener.h>
#include "MatrixOutput.h"

class Matrix : public LoopListener {
public:
	Matrix(MatrixOutput &output, uint8_t width = 16, uint8_t height = 9);
	void setOutput(MatrixOutput &output);
	void begin();
	void drawPixel(int16_t x, int16_t y, uint16_t color);
	void drawPixel(uint8_t i, uint8_t brightness);
	void clear();

	void setRotation(uint8_t rotation);
	uint8_t getRotation() const;
	void drawChar(int32_t x, int32_t y, unsigned char c, uint8_t brightness = 255, bool bigFont = true);
	void drawString(int32_t x, int32_t y, const char* c, uint8_t brightness = 255, bool bigFont = true);
	void drawString(int32_t x, int32_t y, const String &s, uint8_t brightness = 255, bool bigFont = true);
	void setBrightness(uint8_t _brightness);
	uint8_t getBrightness() const;
	void push();
	void drawBitmap(int x, int y, uint width, uint height, uint8_t* data);
	void drawBitmap(int x, int y, uint width, uint height, RGBpixel* data);

	void startAnimation(Animation* _animation, bool loop);
	float getAnimationCompletionRate();
	void stopAnimation();
	void loop(uint _time) override;

private:
	MatrixOutput &output;

	uint8_t width, height, rotation = 2, prevBrightness = 0;
	uint8_t* matrixBuffer = nullptr;
	uint8_t* pastMatrixBuffer = nullptr;

	AnimationFrame* animationFrame = nullptr;
	Animation* animation = nullptr;
	bool animationLoop = false;
	uint currentFrameTime = 0;
	uint animationStartMicros = 0;
};

#endif