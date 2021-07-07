#include "InputListener.h"

void InputListener::buttonPressed(uint i) {}
void InputListener::buttonReleased(uint i) {}
void InputListener::buttonHeld(uint i) {}
void InputListener::buttonHeldRepeat(uint i, uint repeatCount) {}
void InputListener::anyKeyCallback() {}

void InputListener::setButtonHoldAndRepeatTime(uint8_t button, uint32_t holdAndRepeatTime){
	holdAndRepeatTimes.insert({ button, {holdAndRepeatTime, 0} });
}

void InputListener::setButtonHoldTime(uint8_t button, uint32_t holdTime){
	holdTimes.insert({button, {holdTime, false}});

}
