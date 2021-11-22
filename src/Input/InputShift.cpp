#include "InputShift.h"

InputShift::InputShift( uint8_t dataPin, uint8_t clockPin, uint8_t shiftPin) : Input(REG_PIN_MAX) ,dataPin_(dataPin), clockPin_(clockPin), shiftPin_(shiftPin){

}

uint8_t InputShift::shiftInput(uint8_t dataPin, uint8_t clockPin, uint8_t shiftPin){
	uint16_t value = 0;
	uint8_t i;

	digitalWrite(clockPin, LOW);

	digitalWrite(shiftPin, LOW);
	delayMicroseconds(PERIOD);
	digitalWrite(shiftPin, HIGH);

	delayMicroseconds(PERIOD);

	for(i = 0; i < 8; ++i){
		//digitalWrite(clockPin, HIGH);
		value |= ((uint16_t) digitalRead(dataPin)) << i;
		digitalWrite(clockPin, HIGH);
		delayMicroseconds(PERIOD);
		digitalWrite(clockPin, LOW);
		delayMicroseconds(PERIOD);
	}
	return value;
}

void InputShift::scanButtons(){
	for(uint i = 0; i < buttons.size(); i++){
		if((shiftInput(dataPin_, clockPin_, shiftPin_) & (1 << buttons[i]))){
			if(digitalRead(buttons[i])){
				//released
				Input::btnRelease(i);
			}else{
				Input::btnPress(i);
			}
		}
	}
}
