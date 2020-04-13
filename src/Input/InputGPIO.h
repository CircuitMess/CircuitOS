#ifndef CIRCUITOS_INPUTGPIO_H
#define CIRCUITOS_INPUTGPIO_H

#include "Input.h"
#include "../Util/Vector.h"
#include "../Util/Task.h"


#define PIN_MAX 45
#define DEBOUNCE_COUNT 1

typedef uint8_t Button;

class InputGPIO : public Input {
public:
	InputGPIO();
	void setBtnPressCallback(uint8_t pin, void (*callback)()) override;
	void setBtnReleaseCallback(uint8_t pin, void (*callback)()) override;

private:
	void addPinListener(uint8_t pin);
	void scanButtons() override;

};


#endif //CIRCUITOS_INPUTGPIO_H
