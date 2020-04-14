#include "Input.h"
#include "../Util/Debug.h"

Input* Input::instance;

Input::Input(uint8_t _pinNumber) : pinNumber(_pinNumber), btnPressCallback(pinNumber, nullptr),
								   btnReleaseCallback(pinNumber, nullptr), scanTask("InputScanTask", scanTaskFunction){
	instance = this;
}

void Input::start(){
	logln("Starting input");
	scanTask.start();
}

void Input::stop(){
	logln("Stopping input");
	scanTask.stop();
}

void Input::setBtnPressCallback(uint8_t pin, void (* callback)()){
	if(pin >= pinNumber) return;
	registerButton(pin);
	btnPressCallback[pin] = callback;
}

void Input::setBtnReleaseCallback(uint8_t pin, void (* callback)()){
	if(pin >= pinNumber) return;
	registerButton(pin);
	btnReleaseCallback[pin] = callback;
}

void Input::removeBtnPressCallback(uint8_t pin){
	if(pin >= pinNumber) return;
	btnPressCallback[pin] = nullptr;
}

void Input::removeBtnReleaseCallback(uint8_t pin){
	if(pin >= pinNumber) return;
	btnReleaseCallback[pin] = nullptr;
}

void Input::scanTaskFunction(Task* task){
	logln("Input task starting");

	while(task->running){
		vTaskDelay(1);

		if(instance == nullptr) continue;
		instance->scanButtons();
	}
}

Input* Input::getInstance(){
	return instance;
}

void Input::registerButton(uint8_t pin){
	if(buttons.indexOf(pin) != -1) return;
	buttons.push_back(pin);
	btnCount.push_back(0);
	btnState.push_back(0);
}

void Input::btnPress(uint i){
	if(btnCount[i] < DEBOUNCE_COUNT){
		btnCount[i]++;

		if(btnState[i] == 0 && btnCount[i] == DEBOUNCE_COUNT){
			btnState[i] = 1;

			if(btnPressCallback[buttons[i]] != nullptr){
				btnPressCallback[buttons[i]]();
			}
		}
	}
}

void Input::btnRelease(uint i){
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
void Input::update(uint millis)
{
	scanButtons();
}
