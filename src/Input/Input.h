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

	virtual void setBtnPressCallback(uint8_t pin, void (*callback)());
	virtual void setBtnReleaseCallback(uint8_t pin, void (*callback)());

	void removeBtnPressCallback(uint8_t pin);
	void removeBtnReleaseCallback(uint8_t pin);

	static Input* getInstance();

protected:
	uint8_t pinNumber = 0;
	
	std::vector<void(*)()> btnPressCallback;
	std::vector<void(*)()> btnReleaseCallback;
	Vector<uint8_t> buttons;

	std::vector<uint8_t> btnCount; // Read count per button
	std::vector<uint8_t> btnState; // Button state, 0 - released, 1 - pressed

	Task scanTask;
	static Input* instance;
	static void scanTaskFunction(Task* task);
	virtual void scanButtons() = 0;

};


#endif //CIRCUITOS_INPUT_H
