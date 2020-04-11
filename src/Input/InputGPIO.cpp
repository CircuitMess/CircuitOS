#include "InputGPIO.h"
#include "../Util/Debug.h"

InputGPIO* InputGPIO::instance;

InputGPIO::InputGPIO() : scanTask("InputScanTask", InputGPIO::scanTaskFunction){
	instance = this;
}
void InputGPIO::scanTaskFunction(Task* task){
	logln("Input task starting");

	while(task->running){
		vTaskDelay(1);

		if(instance == nullptr) continue;
		instance->scanButtons();
	}
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

InputGPIO* InputGPIO::getInstance(){
	return instance;
}
