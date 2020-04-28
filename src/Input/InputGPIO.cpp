#include "InputGPIO.h"
#include "../Util/Debug.h"

InputGPIO::InputGPIO() : Input(PIN_MAX){

}

void InputGPIO::scanButtons(){
	for(uint i = 0; i < buttons.size(); i++){
		if(digitalRead(buttons[i])){
			//released
			Input::btnRelease(i);
		}else{
			Input::btnPress(i);
		}
	}
}

void InputGPIO::registerButton(uint8_t pin){
	pinMode(pin, INPUT_PULLUP);
	Input::registerButton(pin);
}