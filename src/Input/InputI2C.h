#ifndef CIRCUITOS_INPUTI2C_H
#define CIRCUITOS_INPUTI2C_H

#include "Input.h"
#include "../Util/Vector.h"
#include "../Util/Task.h"

#include <Wire.h>
#include <Keypad_I2Ca.h>

#define PIN_MAX 15
#define DEBOUNCE_COUNT 1



typedef uint8_t Button;

class InputI2C : public Input {
public:
	InputI2C(Keypad_I2Ca* kpd);
	void start();
	void stop();
	static void scanTaskFunction(Task* task);
	static InputI2C* getInstance();

private:
	Task scanTask;
	static InputI2C* instance;
	Keypad_I2Ca* kpd;
	void addPinListener(uint8_t pin);
	void scanButtons();

};


#endif //CIRCUITOS_INPUTI2C_H
