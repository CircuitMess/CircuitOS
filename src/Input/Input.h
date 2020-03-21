#ifndef CIRCUITOS_INPUT_H
#define CIRCUITOS_INPUT_H

#include "../Util/Vector.h"
#include "../Util/Task.h"


#define PIN_MAX 45
#define DEBOUNCE_COUNT 1

typedef uint8_t Button;

class Input {
public:
	Input();

	void start();
	void stop();

	void setBtnPressCallback(uint8_t pin, void (*callback)());
	void setBtnReleaseCallback(uint8_t pin, void (*callback)());

	static void scanTaskFunction(Task* task);

private:
	std::vector<void(*)()> btnPressCallback;
	std::vector<void(*)()> btnReleaseCallback;
	Vector<uint8_t> buttons;

	std::vector<uint8_t> btnCount; // Read count per button
	std::vector<uint8_t> btnState; // Button state, 0 - released, 1 - pressed

	Task scanTask;
	static Input* instance;

	void addPinListener(uint8_t pin);

	void scanButtons();

};


#endif //CIRCUITOS_INPUT_H
