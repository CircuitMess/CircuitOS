#include "InputI2C.h"
#include "../Util/Debug.h"

InputI2C::InputI2C(Keypad_I2Ca* _kpd) : Input(I2C_PIN_MAX) , kpd(_kpd){
}
void InputI2C::start(){
	logln("Starting I2C input");
	kpd->begin();
	Input::start();
}

void InputI2C::stop(){
	logln("Stopping input");
	Input::stop();
}
void InputI2C::setBtnPressCallback(uint8_t pin, void (* callback)()){
	Input::setBtnPressCallback(pin, callback);
	addPinListener(pin);
}
void InputI2C::setBtnReleaseCallback(uint8_t pin, void (* callback)()){
	Input::setBtnReleaseCallback(pin, callback);
	addPinListener(pin);
}
void InputI2C::scanButtons(){
	int portScan = kpd->port_read();
	for(unsigned char i = 0; i < buttons.size(); i++){
		if(!bitRead(portScan, buttons[i])){
			//pressed
			if(btnCount[i] < DEBOUNCE_COUNT){
				btnCount[i]++;

				if(btnState[i] == 0 && btnCount[i] == DEBOUNCE_COUNT){
					btnState[i] = 1;

					if(btnPressCallback[buttons[i]] != nullptr){
						btnPressCallback[buttons[i]]();
					}
				}
			}
		}else{
			//released
			if(btnCount[i] > 0){
				btnCount[i]--;

				if(btnState[i] == 1 && btnCount[i] == 0){
					btnState[i] = 0;

					if(btnReleaseCallback[buttons[i]] != nullptr){
						btnReleaseCallback[buttons[i]]();
					}
				}
			}
		}


	}
}

void InputI2C::addPinListener(uint8_t pin){
	if(buttons.indexOf(pin) != -1) return;

	kpd->pin_mode(pin, INPUT_PULLUP);
	kpd->pin_read(pin);

	buttons.push_back(pin);
	btnCount.push_back(0);
	btnState.push_back(0);
}