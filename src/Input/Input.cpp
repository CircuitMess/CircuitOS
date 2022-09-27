#include "Input.h"
#include "../Util/Debug.h"

Input* Input::instance;

Input::Input(uint8_t _pinNumber) : pinNumber(_pinNumber), btnPressCallback(pinNumber, nullptr),
								   btnReleaseCallback(pinNumber, nullptr),
								   btnHoldCallback(pinNumber, nullptr), btnHoldRepeatCallback(pinNumber, nullptr),
								   btnHoldStart(pinNumber, 0), btnHoldRepeatCounter(pinNumber, 0),
								   btnHoldValue(pinNumber, 0), btnHoldRepeatValue(pinNumber, 0),
								   btnHoldOver(pinNumber, 0), anyKeyCallback(nullptr), anyKeyCallbackReturn(0){
	instance = this;

	listeners.reserve(16);
	addedListeners.reserve(4);
	removedListeners.reserve(4);
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
			if(anyKeyCallback != nullptr){
				if(anyKeyCallbackReturn){
					anyKeyCallback();
					return;
				}else{
					anyKeyCallback();
				}
			}
			btnState[i] = 1;
			if(!btnHoldOver[buttons[i]]){
				btnHoldStart[buttons[i]] = millis();
			}

			for(auto listener : listeners){
				if(mask.find(listener) != mask.end()) continue;

				if(removedListeners.find(listener) != removedListeners.end()) continue;
				listener->buttonPressed(buttons[i]);
				if(removedListeners.find(listener) != removedListeners.end()) continue;
				listener->anyKeyPressed();
				if(removedListeners.find(listener) != removedListeners.end()) continue;
				if(listener->holdTimes.find(buttons[i]) != listener->holdTimes.end() && !listener->holdTimes.find(buttons[i])->second.holdingOver){
						btnHoldStart[buttons[i]] = millis();
						return;
				}
			}
			if(btnPressCallback[buttons[i]] != nullptr){
				btnPressCallback[buttons[i]]();
			}
		}
	}

	clearListeners();
}

void Input::btnRelease(uint i){
	if(btnCount[i] > 0){
		btnCount[i]--;

		if(btnState[i] == 1 && btnCount[i] == 0){
			if(anyKeyCallback != nullptr){
				if(anyKeyCallbackReturn){
					anyKeyCallback();
					return;
				}else{
					anyKeyCallback();
				}
			}
			btnState[i] = 0;
			btnHoldOver[buttons[i]] = false;
			btnHoldStart[buttons[i]] = millis();
			btnHoldRepeatCounter[buttons[i]] = 0;

			for(auto listener : listeners){
				if(mask.find(listener) != mask.end()) continue;

				if(removedListeners.find(listener) != removedListeners.end()) continue;
				listener->buttonReleased(buttons[i]);
				if(listener->holdTimes.find(buttons[i]) != listener->holdTimes.end()){
					listener->holdTimes.find(buttons[i])->second.holdingOver = false;
				}
				if(listener->holdAndRepeatTimes.find(buttons[i]) != listener->holdAndRepeatTimes.end()){
					listener->holdAndRepeatTimes.find(buttons[i])->second.repeatCounter = 0;
				}
			}
			if(btnReleaseCallback[buttons[i]] != nullptr){
				btnReleaseCallback[buttons[i]]();
			}
		}
	}

	clearListeners();
}

void Input::loop(uint _time){
	scanButtons();
	for(uint8_t i = 0; i < buttons.size(); i++){
		uint32_t holdTime = getButtonHeldMillis(buttons[i]);
		if(btnState[i] == 1){
			if(holdTime >= btnHoldValue[buttons[i]] && !btnHoldOver[buttons[i]]){
				if(btnHoldCallback[buttons[i]] != nullptr){
					btnHoldCallback[buttons[i]]();
				}
				btnHoldOver[buttons[i]] = true;
			}
			if(holdTime >= (btnHoldRepeatCounter[buttons[i]] + 1) * btnHoldRepeatValue[buttons[i]]){
				btnHoldRepeatCounter[buttons[i]]++;
				if(btnHoldRepeatCallback[buttons[i]] != nullptr){
					btnHoldRepeatCallback[buttons[i]](btnHoldRepeatCounter[buttons[i]]);
				}
			}

			for(auto listener : listeners){
				if(mask.find(listener) != mask.end()) continue;
				if(removedListeners.find(listener) != removedListeners.end()) continue;

				auto search = listener->holdTimes.find(buttons[i]);
				if(search != listener->holdTimes.end() && holdTime >= search->second.time && !search->second.holdingOver){
					listener->buttonHeld(buttons[i]);
					search->second.holdingOver = true;
				}
				auto searchRepeat = listener->holdAndRepeatTimes.find(buttons[i]);
				if(searchRepeat != listener->holdAndRepeatTimes.end() && holdTime >= (searchRepeat->second.repeatCounter + 1) * searchRepeat->second.time){
					searchRepeat->second.repeatCounter++;
					listener->buttonHeldRepeat(buttons[i], searchRepeat->second.repeatCounter);
				}
			}
		}
	}

	clearListeners();
}

void Input::setButtonHeldCallback(uint8_t pin, uint32_t holdTime, void (* callback)()){
	if(pin >= pinNumber) return;
	registerButton(pin);
	btnHoldCallback[pin] = callback;
	btnHoldValue[pin] = holdTime;
}

void Input::setButtonHeldRepeatCallback(uint8_t pin, uint32_t periodTime, void (* callback)(uint)){
	if(pin >= pinNumber) return;
	registerButton(pin);
	btnHoldRepeatCallback[pin] = callback;
	btnHoldRepeatValue[pin] = periodTime;
}

void Input::removeButtonHeldCallback(uint8_t pin){
	btnHoldCallback[pin] = nullptr;
	btnHoldValue[pin] = 0;
}

void Input::removeButtonHeldRepeatCallback(uint8_t pin){
	btnHoldRepeatCallback[pin] = nullptr;
	btnHoldRepeatValue[pin] = 0;
}

uint32_t Input::getButtonHeldMillis(uint8_t pin){
	if(pin >= pinNumber) return 0;
	return millis() - btnHoldStart[pin];
}

bool Input::getButtonState(uint8_t pin){
	if(pin >= btnState.size()) return false;
	return btnState[pin];
}

void Input::setAnyKeyCallback(void (* callback)(), bool returnAfterCallback){
	anyKeyCallback = callback;
	anyKeyCallbackReturn = returnAfterCallback;
}

void Input::preregisterButtons(Vector<uint8_t> pins){
	for(const uint8_t pin : pins){
		registerButton(pin);
	}
}

void Input::addListener(InputListener* listener){
	if(listeners.indexOf(listener) != -1 || addedListeners.find(listener) != removedListeners.end()) return;
	addedListeners.insert(listener);
	removedListeners.erase(listener);
}

void Input::removeListener(InputListener* listener){
	if(listeners.indexOf(listener) == -1 || removedListeners.find(listener) != removedListeners.end()) return;
	removedListeners.insert(listener);
	mask.erase(listener);
}

void Input::clearListeners(){
	for(const auto& listener : removedListeners){
		uint i = listeners.indexOf(listener);
		if(i == (uint) -1) continue;
		listeners.remove(i);
	}

	removedListeners.clear();

	for(const auto& listener : addedListeners){
		uint i = listeners.indexOf(listener);
		if(i != (uint) -1) continue;
		listeners.push_back(listener);

		for(auto pair : listener->holdTimes){
			pair.second.holdingOver = false;
		}

		for(auto pair : listener->holdAndRepeatTimes){
			pair.second.repeatCounter = 0;
		}

		for(int i = 0; i < pinNumber; i++){
			auto p = listener->holdTimes.find(buttons[i]);
			if(p == listener->holdTimes.end()) continue;

			if(btnState[buttons[i]]){
				p->second.holdingOver = true;
			}
		}
	}

	addedListeners.clear();
}

void Input::maskAll(){
	for(auto listener : listeners){
		mask.insert(listener);
	}
}

void Input::unmaskAll(){
	mask.clear();
}

void Input::addMask(InputListener* listener){
	mask.insert(listener);
}

void Input::removeMask(InputListener* listener){
	mask.erase(listener);
}
