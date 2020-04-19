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
	{
		Serial.println("before btn crit");
		delay(5);
		if(mutex->lock())
		{
			Serial.println("btn crit");
			delay(5);
			int portScan = i2c->portRead();
			mutex->unlock();
			Serial.println("after btn crit");
			delay(5);
			// Serial.println(portScan, BIN);

			for(uint i = 0; i < buttons.size(); i++){
				if(!bitRead(portScan, buttons[i])){
					Input::btnPress(i);
				}else{
					Input::btnRelease(i);
				}
			}
		}
	}
// entering critical
// exiting critical
// before btn crit
// btn crit
// after btn crit
// before btn crit
// btn crit
// after btn crit
// before btn crit
// btn crit
// after btn crit
// before btn crit
// btn crit
// after btn crit
// before btn crit
// btn crit
// after btn crit
// before btn crit
// btn crit
// after btn crit
// before btn crit
// btn crit
// after btn crit
// before btn crit
// before critical
// btn crit
// entering critical
// after btn crit
// toggel
// exiting critical
	else
	{
		int portScan = i2c->portRead();
		for(uint i = 0; i < buttons.size(); i++){
			if(!bitRead(portScan, buttons[i])){
				Input::btnPress(i);
			}else{
				Input::btnRelease(i);
			}
		}
	}
	
}

void InputI2C::registerButton(uint8_t pin){
	if(mutex != nullptr)
	{
		if(mutex->lock())
		{
			i2c->pinMode(pin, INPUT_PULLUP);
			mutex->unlock();
			Input::registerButton(pin);
		}
	}
	else
	{
		i2c->pinMode(pin, INPUT_PULLUP);
		Input::registerButton(pin);
	}
	
}