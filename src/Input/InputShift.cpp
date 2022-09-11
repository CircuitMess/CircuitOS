#include "InputShift.h"

#define PERIOD 1
#define LH(pin) do { digitalWrite((pin), LOW); delayMicroseconds(PERIOD); digitalWrite((pin), HIGH); delayMicroseconds(PERIOD); } while(0)
#define HL(pin) do { digitalWrite((pin), HIGH); delayMicroseconds(PERIOD); digitalWrite((pin), LOW); delayMicroseconds(PERIOD); } while(0)

InputShift::InputShift(uint8_t dataPin, uint8_t clockPin, uint8_t loadPin, uint8_t numButtons) : dataPin(dataPin), clockPin(clockPin), loadPin(loadPin),
numButtons(numButtons), numShifts(ceil((float) numButtons / 8.0f)), Input(numButtons){

	states.resize(numShifts * 8, true);

	for(int i = 0; i < numButtons; i++){
		InputShift::registerButton(i);
	}
}

void InputShift::begin(){
	pinMode(dataPin, INPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(loadPin, OUTPUT);
}

void InputShift::scanButtons(){
	digitalWrite(clockPin, LOW);
	LH(loadPin);

	for(int i = 0; i < numShifts * 8; i++){
		states[numShifts * 8 - i - 1] = digitalRead(dataPin) == HIGH;
		HL(clockPin);
	}

	for(int i = 0; i < numButtons; i++){
		if(states[i]){
			Input::btnRelease(i);
		}else{
			Input::btnPress(i);
		}
	}
}

