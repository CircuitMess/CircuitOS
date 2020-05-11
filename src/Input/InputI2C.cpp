#include "InputI2C.h"
#include "../Util/Debug.h"

InputI2C::InputI2C(I2cExpander* _i2c, Mutex* _i2cMutex) : Input(I2C_PIN_MAX) , i2c(_i2c), mutex(_i2cMutex){

}

void InputI2C::start(){
	Input::start();
	logln("Started I2C input");
}

void InputI2C::scanButtons(){
	if(mutex != nullptr)
		mutex->lock();
	int portScan = i2c->portRead();
	if(mutex != nullptr)
		mutex->unlock();
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
	if(mutex != nullptr)
		mutex->lock();
	i2c->pinMode(pin, INPUT_PULLUP);
	if(mutex != nullptr)
		mutex->unlock();
	Input::registerButton(pin);
}