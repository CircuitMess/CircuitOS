#include "Input.h"
#include "../Util/Debug.h"

Input* Input::instance;

Input::Input(uint8_t _pinNumber) : pinNumber(_pinNumber), btnPressCallback(pinNumber, nullptr),
								   btnReleaseCallback(pinNumber, nullptr),
								   btnHoldCallback(pinNumber, nullptr), btnHoldRepeatCallback(pinNumber, nullptr),
								   btnHoldStart(pinNumber, 0), btnHoldRepeatCounter(pinNumber, 0),
								   btnHoldValue(pinNumber, 0), btnHoldRepeatValue(pinNumber, 0),
								   btnHoldOver(pinNumber, 0){
	instance = this;
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
			if(!btnHoldOver[buttons[i]])
			{
				btnHoldStart[buttons[i]] = millis();
			}
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
			btnHoldOver[buttons[i]] = 0;
			btnHoldStart[buttons[i]] = millis();
			btnHoldRepeatCounter[buttons[i]] = 0;

			if(btnReleaseCallback[buttons[i]] != nullptr){
				btnReleaseCallback[buttons[i]]();
			}
		}
	}
}
void Input::update(uint _millis)
{
	scanButtons();
	for(uint8_t i = 0; i < buttons.size(); i++)
	{
		uint32_t holdTime = getButtonHeldMillis(buttons[i]);
		if(btnState[i] == 1 && (btnHoldRepeatCallback[buttons[i]] != nullptr || btnHoldCallback[buttons[i]] != nullptr))
		{
			
			if(holdTime >= btnHoldValue[buttons[i]] && !btnHoldOver[buttons[i]])
			{
				if(btnHoldCallback[buttons[i]] != nullptr)
				{
					btnHoldCallback[buttons[i]]();
				}
				btnHoldOver[buttons[i]] = 1;
			}
			if(holdTime >= (btnHoldRepeatCounter[buttons[i]] + 1)*btnHoldRepeatValue[buttons[i]])
			{
				btnHoldRepeatCounter[buttons[i]]++;
				if(btnHoldRepeatCallback[buttons[i]] != nullptr)
				{
					btnHoldRepeatCallback[buttons[i]](btnHoldRepeatCounter[buttons[i]]);
				}
			}
		}
	}
}
void Input::setButtonHeldCallback(uint8_t pin, uint32_t holdTime, void (*callback)())
{
	if(pin >= pinNumber) return;
	registerButton(pin);
	btnHoldCallback[pin] = callback;
	btnHoldValue[pin] = holdTime;
}
void Input::setButtonHeldRepeatCallback(uint8_t pin, uint32_t periodTime, void (*callback)(uint))
{
	if(pin >= pinNumber) return;
	registerButton(pin);
	btnHoldRepeatCallback[pin]=callback;
	btnHoldRepeatValue[pin] = periodTime;
}
uint32_t Input::getButtonHeldMillis(uint8_t pin)
{
	if(pin >= pinNumber) return 0;
	return millis() - btnHoldStart[pin];
}