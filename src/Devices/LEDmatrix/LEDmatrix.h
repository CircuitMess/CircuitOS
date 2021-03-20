#ifndef SPENCER_LEDMATRIX_H
#define SPENCER_LEDMATRIX_H
/*
Modified version of Adafruits IS31FL3731 library (https://github.com/adafruit/Adafruit_IS31FL3731)

This is a stripped-down version with no Adafruit-GFX library inheritance.
*/

#include <Arduino.h>
#include "Animation.h"
#include <Loop/LoopListener.h>

#define ISSI_ADDR_DEFAULT 0x74

#define ISSI_REG_CONFIG 0x00
#define ISSI_REG_CONFIG_PICTUREMODE 0x00
#define ISSI_REG_CONFIG_AUTOPLAYMODE 0x08
#define ISSI_REG_CONFIG_AUDIOPLAYMODE 0x18

#define ISSI_CONF_PICTUREMODE 0x00
#define ISSI_CONF_AUTOFRAMEMODE 0x04
#define ISSI_CONF_AUDIOMODE 0x08

#define ISSI_REG_PICTUREFRAME 0x01

#define ISSI_REG_SHUTDOWN 0x0A
#define ISSI_REG_AUDIOSYNC 0x06

#define ISSI_COMMANDREGISTER 0xFD
#define ISSI_BANK_FUNCTIONREG 0x0B // helpfully called 'page nine'

class LEDmatrixImpl : public LoopListener
{
public:
	LEDmatrixImpl(uint8_t width = 16, uint8_t height = 9);
	bool begin(uint8_t sda = 22, uint8_t scl = 21, uint8_t addr = ISSI_ADDR_DEFAULT);
	void drawPixel(int16_t x, int16_t y, uint16_t color);
	void drawPixel(uint8_t i, uint8_t brightness);
	void clear(void);

	void setLEDPWM(uint8_t lednum, uint8_t pwm, uint8_t bank = 0);
	void audioSync(bool sync);
	void setFrame(uint8_t b);
	void displayFrame(uint8_t frame);

	void setRotation(uint8_t rotation);
	uint8_t getRotation();
	void drawChar(int32_t x, int32_t y, unsigned char c, uint8_t brightness = 255, bool bigFont = 1);
	void drawString(int32_t x, int32_t y, const char* c, uint8_t brightness = 255, bool bigFont = 1);
	void setBrightness(uint8_t _brightness);
	uint8_t getBrightness();
	void push();
	void drawBitmap(int x, int y, uint width, uint height, uint8_t* data);
	void drawBitmap(int x, int y, uint width, uint height, RGBpixel* data);

	void startAnimation(Animation* _animation, bool loop);
	float getAnimationCompletionRate();
	void stopAnimation();
	void loop(uint _time) override;

private:
	void selectBank(uint8_t bank);
	void writeRegister8(uint8_t bank, uint8_t reg, uint8_t data);
	uint8_t readRegister8(uint8_t bank, uint8_t reg);
	uint8_t _i2caddr, ///< The I2C address we expect to find the chip
		_frame;       ///< The frame (of 8) we are currently addressing
	uint8_t width, height, brightness = 20, rotation = 2, prevBrightness = 0;
	uint8_t *matrixBuffer = nullptr;
	uint8_t *pastMatrixBuffer = nullptr;

	AnimationFrame* animationFrame = nullptr;
	Animation* animation = nullptr;
	bool animationLoop = 0;
	uint currentFrameTime = 0;
	uint animationStartMicros = 0;
};

#endif