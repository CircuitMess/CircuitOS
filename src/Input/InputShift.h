#ifndef CIRCUITOS_INPUTSHIFT_H
#define CIRCUITOS_INPUTSHIFT_H

#include "../Loop/LoopListener.h"
#include "Input.h"
#define REG_PIN_MAX 40
#define PERIOD 1

class InputShift : public Input {
public:
	InputShift( uint8_t dataPin, uint8_t clockPin, uint8_t shiftPin);

	uint8_t shiftInput(uint8_t dataPin, uint8_t clockPin, uint8_t shiftPin);

private:
	uint8_t dataPin;
	uint8_t clockPin;
	uint8_t shiftPin = 1;
	uint8_t shiftsNum;
protected:
	void scanButtons() override;

};

#endif //CIRCUITOS_INPUTSHIFT_H
