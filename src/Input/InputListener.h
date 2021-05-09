#ifndef CIRCUITOS_INPUTLISTENER_H
#define CIRCUITOS_INPUTLISTENER_H

#include <Arduino.h>

class Input;

class InputListener {
	friend Input;

private:
	virtual void buttonPressed(uint i);
	virtual void buttonReleased(uint i);
	virtual void buttonHeld(uint i);
	virtual void buttonHeldRepeat(uint i, uint repeatCount);
	virtual void anyKeyCallback();
};


#endif //CIRCUITOS_INPUTLISTENER_H
