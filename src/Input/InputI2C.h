#ifndef CIRCUITOS_INPUTI2C_H
#define CIRCUITOS_INPUTI2C_H

#include "Input.h"
#include "../Util/Vector.h"
#include "../Util/Task.h"

#include <Wire.h>
#include "Keypad_I2Ca/Keypad_I2Ca.h"

#define I2C_PIN_MAX 15
#define DEBOUNCE_COUNT 1

class InputI2C : public Input {
public:
	InputI2C(Keypad_I2Ca* kpd);

	void start() override;
	
private:
	Keypad_I2Ca* kpd;
	void registerButton(uint8_t pin) override;
	void scanButtons() override;

};


#endif //CIRCUITOS_INPUTI2C_H
