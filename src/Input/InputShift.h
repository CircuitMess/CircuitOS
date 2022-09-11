#ifndef CIRCUITOS_INPUTSHIFT_H
#define CIRCUITOS_INPUTSHIFT_H

#include "Input.h"

class InputShift : public Input {
public:
	InputShift(uint8_t dataPin, uint8_t clockPin, uint8_t loadPin, uint8_t numButtons);
	void begin();

protected:
	void scanButtons() override;

private:
	uint8_t dataPin;
	uint8_t clockPin;
	uint8_t loadPin;

	uint8_t numButtons;
	uint8_t numShifts;

	std::vector<bool> states;

};

#endif //CIRCUITOS_INPUTSHIFT_H
