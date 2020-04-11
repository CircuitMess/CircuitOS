#include "Input.h"
#include "../Util/Debug.h"

Input* Input::instance;

Input::Input() : btnPressCallback(PIN_MAX, nullptr), btnReleaseCallback(PIN_MAX, nullptr), scanTask("InputScanTask", NULL){
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
	if(pin >= PIN_MAX) return;

	btnPressCallback[pin] = callback;
	addPinListener(pin);
}

void Input::setBtnReleaseCallback(uint8_t pin, void (* callback)()){
	if(pin >= PIN_MAX) return;

	btnReleaseCallback[pin] = callback;
	addPinListener(pin);
}

void Input::removeBtnPressCallback(uint8_t pin){
	if(pin >= PIN_MAX) return;
	btnPressCallback[pin] = nullptr;
}

void Input::removeBtnReleaseCallback(uint8_t pin){
	if(pin >= PIN_MAX) return;
	btnReleaseCallback[pin] = nullptr;

}

void Input::addPinListener(uint8_t pin){
	if(buttons.indexOf(pin) != -1) return;

	pinMode(pin, INPUT_PULLUP);
	digitalRead(pin);

	buttons.push_back(pin);
	btnCount.push_back(0);
	btnState.push_back(0);
}