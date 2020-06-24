#include "InputI2C.h"
#include "I2cExpander.h"

InputI2C::InputI2C(I2cExpander* _i2c) : Input(I2C_PIN_MAX) , i2c(_i2c){

}

void InputI2C::scanButtons(){
	int portScan = i2c->portRead();
	for(uint i = 0; i < buttons.size(); i++){
		if(bitRead(portScan, buttons[i])){
			Input::btnRelease(i);
		}
		else{
			Input::btnPress(i);
		}
		
	}
}

void InputI2C::registerButton(uint8_t pin){
	i2c->pinMode(pin, INPUT_PULLUP);
	Input::registerButton(pin);
}