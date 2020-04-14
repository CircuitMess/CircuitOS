#ifndef CIRCUITOS_INPUT_H
#define CIRCUITOS_INPUT_H

#include "../Util/Vector.h"
#include "../Util/Task.h"
#include "../Update/UpdateListener.h"
#define PIN_MAX 45
#define DEBOUNCE_COUNT 1

class Input : public UpdateListener {
public:
	Input(uint8_t _pinNumber);

	virtual void start();
	virtual void stop();

	virtual void setBtnPressCallback(uint8_t pin, void (*callback)());
	virtual void setBtnReleaseCallback(uint8_t pin, void (*callback)());

	virtual void removeBtnPressCallback(uint8_t pin);
	virtual void removeBtnReleaseCallback(uint8_t pin);

	static Input* getInstance();

protected:
	uint8_t pinNumber = 0;
	
	std::vector<void(*)()> btnPressCallback;
	std::vector<void(*)()> btnReleaseCallback;

	Task scanTask;
	static Input* instance;
	static void scanTaskFunction(Task* task);
	virtual void scanButtons() = 0;

	virtual void registerButton(uint8_t pin);

	Vector<uint8_t> buttons;
	std::vector<uint8_t> btnCount; // Read count per button
	std::vector<uint8_t> btnState; // Button state, 0 - released, 1 - pressed

	void btnPress(uint i);
	void btnRelease(uint );
	void update(uint millis) override;
};


#endif //CIRCUITOS_INPUT_H
