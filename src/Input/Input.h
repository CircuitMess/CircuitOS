#ifndef CIRCUITOS_INPUT_H
#define CIRCUITOS_INPUT_H

#include "../Util/Vector.h"
#include "../Util/Task.h"


#define PIN_MAX 45
#define DEBOUNCE_COUNT 1

typedef uint8_t Button;

class Input {
public:
	Input(uint8_t _pinNumber);

	virtual void start();
	virtual void stop();

	void setBtnPressCallback(uint8_t pin, void (*callback)());
	void setBtnReleaseCallback(uint8_t pin, void (*callback)());

	void removeBtnPressCallback(uint8_t pin);
	void removeBtnReleaseCallback(uint8_t pin);

protected:
	std::vector<void(*)()> btnPressCallback;
	std::vector<void(*)()> btnReleaseCallback;
	Vector<uint8_t> buttons;

	std::vector<uint8_t> btnCount; // Read count per button
	std::vector<uint8_t> btnState; // Button state, 0 - released, 1 - pressed

	Task scanTask;
	static Input* instance;
	void scanTaskFunction(Task* task);
	virtual void addPinListener(uint8_t pin) = 0;
	virtual void scanButtons() = 0;
	uint8_t pinNumber;

};


#endif //CIRCUITOS_INPUT_H
