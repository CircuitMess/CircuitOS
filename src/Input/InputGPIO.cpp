#include "InputGPIO.h"
#include "../Util/Debug.h"

InputGPIO::InputGPIO() : Input(PIN_MAX){

}

void InputGPIO::scanButtons(){
	for(uint i = 0; i < buttons.size(); i++){
		if(!digitalRead(buttons[i])){
			Input::btnPress(i);
		}else{
			//released
			Input::btnRelease(i);
		}
	}
}

void InputGPIO::registerButton(uint8_t pin){
	Input::registerButton(pin);

	pinMode(pin, INPUT_PULLUP);
	digitalRead(pin);
}