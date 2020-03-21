#include "Input.h"

Input* Input::instance;

Input::Input() : btnPressCallback(PIN_MAX, nullptr), btnReleaseCallback(PIN_MAX, nullptr), scanTask("InputScanTask", scanTaskFunction){
	instance = this;
}

void Input::start(){
	scanTask.start();
}

void Input::stop(){
	Serial.println("Stopping input");
	scanTask.stop();
}

void Input::setBtnPressCallback(uint8_t pin, void (* callback)()){
	if(pin >= PIN_MAX) return;

	btnPressCallback[pin] = callback;
	addPinListener(pin);
}

void Input::setBtnReleaseCallback(uint8_t pin, void (* callback)()){
	if(pin >= PIN_MAX) return;

	btnReleaseCallback[pin] = callback;
	addPinListener(pin);
}

void Input::addPinListener(uint8_t pin){
	if(buttons.indexOf(pin) != -1) return;

	pinMode(pin, INPUT_PULLUP);
	digitalRead(pin);

	buttons.push_back(pin);
	btnCount.push_back(0);
	btnState.push_back(0);
}

void Input::scanTaskFunction(Task* task){
	while(task->running){
		vTaskDelay(1);

		if(instance == nullptr) continue;
		instance->scanButtons();
	}
}

void Input::scanButtons(){
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