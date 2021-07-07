#ifndef CIRCUITOS_INPUTLISTENER_H
#define CIRCUITOS_INPUTLISTENER_H

#include <Arduino.h>
#include <map>

class Input;

struct HoldData {
	uint32_t time;
	bool holdingOver;
};
struct HoldRepeatData {
	uint32_t time;
	uint32_t repeatCounter;
};

class InputListener {
	friend Input;

protected:
	void setButtonHoldTime(uint8_t button, uint32_t holdTime);
	void setButtonHoldAndRepeatTime(uint8_t button, uint32_t holdAndRepeatTime);

private:
	virtual void buttonPressed(uint i);
	virtual void buttonReleased(uint i);
	virtual void buttonHeld(uint i);
	virtual void buttonHeldRepeat(uint i, uint repeatCount);
	virtual void anyKeyCallback();

	std::map<uint8_t, HoldData> holdTimes;
	std::map<uint8_t, HoldRepeatData> holdAndRepeatTimes;
};


#endif //CIRCUITOS_INPUTLISTENER_H
