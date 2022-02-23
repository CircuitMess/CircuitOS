#ifndef CIRCUITOS_SHIFTMATRIXOUTPUT_H
#define CIRCUITOS_SHIFTMATRIXOUTPUT_H

#include "MatrixOutput.h"
#include "../../Sync/Mutex.h"

class ShiftMatrixOutput : public MatrixOutput {
public:
	ShiftMatrixOutput(uint width, uint height);
	void init() override;
	void push(void* data) override;

	void setPins(uint8_t dataPin, uint8_t clockPin, uint8_t loadPin);
private:
	uint8_t dataPin = 0, clockPin = 0, loadPin = 0, numShifts = 0;
	uint8_t* matrixBuffer;
	Mutex mutex;

	void pushToShift();
	static ShiftMatrixOutput* instance;
	hw_timer_t* timer = nullptr;
	static void timerInterrupt();
	uint32_t pushInterval = 50; //ms
};


#endif //CIRCUITOS_SHIFTMATRIXOUTPUT_H
