#include "InputI2C.h"
#include "../Util/Debug.h"

InputI2C::InputI2C(Keypad_I2Ca* _kpd) : Input(I2C_PIN_MAX) , kpd(_kpd){

}

void InputI2C::start(){
	Input::start();
	logln("Started I2C input");
}

void InputI2C::scanButtons(){
	int portScan = kpd->port_read();

	for(uint i = 0; i < buttons.size(); i++){
		if(!bitRead(portScan, buttons[i])){
			Input::btnPress(i);
		}else{
			Input::btnRelease(i);
		}
	}
}

void InputI2C::registerButton(uint8_t pin){
	kpd->pin_mode(pin, INPUT_PULLUP);
	Input::registerButton(pin);
}