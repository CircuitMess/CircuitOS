#ifndef CIRCUITOS_INPUTI2C_H
#define CIRCUITOS_INPUTI2C_H

#include "Input.h"

#define I2C_PIN_MAX 16
#define DEBOUNCE_COUNT 1

class I2cExpander;

class InputI2C : public Input {
public:
	InputI2C(I2cExpander* _i2c);
	
private:
	I2cExpander* i2c;
	void registerButton(uint8_t pin) override;
	void scanButtons() override;
};


#endif //CIRCUITOS_INPUTI2C_H
