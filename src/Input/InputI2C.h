#ifndef CIRCUITOS_INPUTI2C_H
#define CIRCUITOS_INPUTI2C_H

#include "Input.h"
#include "../Util/Vector.h"
#include "../Util/Task.h"
#include "../Sync/Mutex.h"
#include <Wire.h>
#include "I2cExpander.h"

#define I2C_PIN_MAX 16
#define DEBOUNCE_COUNT 1

class InputI2C : public Input {
public:
	InputI2C(I2cExpander* _i2c, Mutex* _i2cMutex = nullptr);

	void start() override;
	
private:
	I2cExpander* i2c;
	void registerButton(uint8_t pin) override;
	void scanButtons() override;
	Mutex* mutex;
};


#endif //CIRCUITOS_INPUTI2C_H
