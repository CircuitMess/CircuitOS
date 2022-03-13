#ifndef CIRCUITOS_IS31FL3731_H
#define CIRCUITOS_IS31FL3731_H

/*
Modified version of Adafruits IS31FL3731 library (https://github.com/adafruit/Adafruit_IS31FL3731)

This is a stripped-down version with no Adafruit-GFX library inheritance.
*/

#include <Wire.h>
#include "MatrixOutput.h"

class IS31FL3731 : public MatrixOutput {
public:
	IS31FL3731(TwoWire& Wire = ::Wire, uint8_t addr = 0x74);
	void init() override;
	void push(const MatrixPixelData& data) override;

private:
	TwoWire& Wire;
	uint8_t addr;

	void audioSync(bool sync);

	/**
	 * Write one byte to a register located in a given bank.
	 * @param bank IS31 bank to write the register location
	 * @param reg Offset into the bank to write
	 * @param data Byte value
	 */
	void writeRegister8(uint8_t bank, uint8_t reg, uint8_t data);

	/**
	 * Read one byte from a register located in a given bank.
	 * @param bank IS31 bank to read the register location
	 * @param reg Offset into the bank to read
	 * @return 1 byte value
	 */
	uint8_t readRegister8(uint8_t bank, uint8_t reg);

	/**
	 * Select bank for future reads and writes.
	 * @param bank IS31 bank index
	 */
	void selectBank(uint8_t bank);

};


#endif //CIRCUITOS_IS31FL3731_H
