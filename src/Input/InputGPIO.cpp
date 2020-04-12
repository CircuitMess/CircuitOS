#include "InputGPIO.h"
#include "../Util/Debug.h"

InputGPIO::InputGPIO() : Input(PIN_MAX){
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