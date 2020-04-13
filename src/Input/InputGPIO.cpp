#include "InputGPIO.h"
#include "../Util/Debug.h"

InputGPIO::InputGPIO() : Input(PIN_MAX){
}
void InputGPIO::setBtnPressCallback(uint8_t pin, void (* callback)()){
	Input::setBtnPressCallback(pin, callback);
	addPinListener(pin);
}
void InputGPIO::setBtnReleaseCallback(uint8_t pin, void (* callback)()){
	Input::setBtnReleaseCallback(pin, callback);
	addPinListener(pin);
}
void InputGPIO::scanButtons(){
	for(unsigned char i = 0; i < buttons.size(); i++){
		if(!digitalRead(buttons[i])){
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
void InputGPIO::addPinListener(uint8_t pin){
	if(buttons.indexOf(pin) != -1) return;
	pinMode(pin, INPUT_PULLUP);
	digitalRead(pin);
	buttons.push_back(pin);
	btnCount.push_back(0);
	btnState.push_back(0);
}