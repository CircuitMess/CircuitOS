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
	static void scanTaskFunction(Task* task);
	static InputGPIO* getInstance();

private:
	Task scanTask;
	static InputGPIO* instance;

	void addPinListener(uint8_t pin);

	void scanButtons();

};


#endif //CIRCUITOS_INPUTGPIO_H
