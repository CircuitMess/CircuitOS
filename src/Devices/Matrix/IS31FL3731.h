#ifndef CIRCUITOS_IS31FL3731_H
#define CIRCUITOS_IS31FL3731_H

/*
Modified version of Adafruits IS31FL3731 library (https://github.com/adafruit/Adafruit_IS31FL3731)

This is a stripped-down version with no Adafruit-GFX library inheritance.
*/

#include "MatrixOutput.h"

#define ISSI_ADDR_DEFAULT 0x74

class IS31FL3731 : public MatrixOutput {
public:
	IS31FL3731(uint width, uint height);
	void init() override;
	void push(void* data) override;

	void setI2C(uint8_t sda = 22, uint8_t scl = 21, uint8_t addr = ISSI_ADDR_DEFAULT);

private:
	uint8_t sda, scl,
			_i2caddr, ///< The I2C address we expect to find the chip
	_frame;       ///< The frame (of 8) we are currently addressing

	void setLEDPWM(uint8_t lednum, uint8_t pwm, uint8_t bank = 0);
	void audioSync(bool sync);
	void setFrame(uint8_t b);
	void displayFrame(uint8_t frame);

	void selectBank(uint8_t bank);
	void writeRegister8(uint8_t bank, uint8_t reg, uint8_t data);
	uint8_t readRegister8(uint8_t bank, uint8_t reg);
};


#endif //CIRCUITOS_IS31FL3731_H
