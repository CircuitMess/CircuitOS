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

	virtual void setButtonHeldCallback(uint8_t pin, uint32_t holdTime, void (*callback)());
	virtual void setButtonHeldRepeatCallback(uint8_t pin, uint32_t periodTime, void (*callback)());
	virtual uint32_t getButtonHeldMillis(uint8_t pin);
	static Input* getInstance();

protected:
	uint8_t pinNumber = 0;
	
	std::vector<void(*)()> btnPressCallback;
	std::vector<void(*)()> btnReleaseCallback;
	std::vector<void(*)()> btnHoldCallback;
	std::vector<void(*)()> btnHoldRepeatCallback;

	Task scanTask;
	static Input* instance;
	static void scanTaskFunction(Task* task);
	static uint32_t scanTaskMillis;
	virtual void scanButtons() = 0;

	virtual void registerButton(uint8_t pin);

	Vector<uint8_t> buttons;
	std::vector<uint8_t> btnCount; // Read count per button
	std::vector<uint8_t> btnState; // Button state, 0 - released, 1 - pressed
	std::vector<uint32_t> btnHoldTime; //Counter in ms when a button is held
	std::vector<uint32_t> btnHoldValue; //Value in ms that the callback will be triggered after
	std::vector<uint32_t> btnHoldRepeatValue; //Value in ms that the callback will be triggered after periodically
	std::vector<uint32_t> btnHoldRepeatCounter;
	std::vector<bool> btnHoldOver;

	void btnPress(uint i);
	void btnRelease(uint );
	void update(uint millis) override;
	void btnHeld(uint8_t i, uint32_t millis);

};


#endif //CIRCUITOS_INPUT_H
