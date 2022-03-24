#ifndef CIRCUITOS_AW9523_H
#define CIRCUITOS_AW9523_H

#include <Arduino.h>
#include <Wire.h>

class AW9523 {
public:
	AW9523(TwoWire& Wire = ::Wire, uint8_t addr = 0x58);
	bool begin();

	/**
	 * Sends a software reset. Blocks for 50us after I2C transmission ends.
	 */
	void reset();

	enum PinMode { IN, OUT, LED };

	/**
	 * Set pin mode:
	 *   IN - GPIO input
	 *   OUT - GPIO output
	 *   LED - GPIO output with current control. Use dim(pin, factor) function to set dimming factor.
	 * @param pin Pin index
	 * @param mode Pin mode
	 */
	void pinMode(uint8_t pin, PinMode mode);

	/**
	 * Read pin input state.
	 * @param pin Pin index
	 * @return State - true for high, false for low
	 */
	bool read(uint8_t pin);

	/**
	 * Set pin output state.
	 * @param pin Pin index
	 * @param state True for high, false for low
	 */
	void write(uint8_t pin, bool state);

	/**
	 * Set LED dimming factor for pin.
	 * @param pin Pin index
	 * @param factor Dimming factor. Range 0-255
	 */
	void dim(uint8_t pin, uint8_t factor);

	/**
	 * Enable or disable interrupt triggering for pin.
	 * @param pin Pin index
	 * @param enabled
	 */
	void setInterrupt(uint8_t pin, bool enabled);

	enum CurrentLimit : uint8_t {
		IMAX, // I_max
		IMAX_3Q, // I_max * 3/4
		IMAX_2Q, // I_max * 2/4
		IMAX_1Q // I_max * 1/4
	};

	/**
	 * Set LED drive current limit. Only applies to pins configured as LED output. I_max is 37mA.
	 *   IMAX - full I_max value (37mA)
	 *   IMAX_3Q - 3/4 * I_max
	 *   IMAX_2Q - 2/4 * I_max
	 *   IMAX_1Q - 1/4 * I_max
	 */
	void setCurrentLimit(CurrentLimit limit);

private:
	TwoWire& Wire;
	const uint8_t addr;

	static const uint8_t dimmap[16];

	struct Regs {
		uint8_t conf = 0;
		uint8_t dir[2] = { 0, 0 };
		uint8_t output[2] = { 0, 0 };
		uint8_t intr[2] = { 0, 0 };
		uint8_t mode[2] = { 0xff, 0xff };
		uint8_t dim[16] = { 0 };
	} regs;

	uint8_t readReg(uint8_t reg) const;
	void writeReg(uint8_t reg, const uint8_t* data, size_t size) const;
	void writeReg(uint8_t reg, uint8_t data) const;
};


#endif //CIRCUITOS_AW9523_H
