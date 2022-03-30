#ifndef CIRCUITOS_DELAYEDMATRIXOUTPUT_H
#define CIRCUITOS_DELAYEDMATRIXOUTPUT_H

#include <cstdlib>
#include "MatrixOutput.h"
#include "../../Loop/LoopListener.h"

class DelayedMatrixOutput : public MatrixOutput, public LoopListener {
public:
	/**
	 * @brief Constructor
	 * @param out MatrixOutput to pushDelay
	 * @param pushDelay Minimum pushDelay between push calls in ms, everything before the pushDelay time will not be pushed
	 */
	DelayedMatrixOutput(MatrixOutput* out, uint32_t pushDelay);
	void init() override;
	void push(const MatrixPixelData& data) override;
	void loop(uint micros) override;

private:
	MatrixOutput* out;
	const uint32_t pushDelay;

	uint32_t lastPush = 0;
	bool pushNeeded = false;
	MatrixPixelData data;
};


#endif //CIRCUITOS_DELAYEDMATRIXOUTPUT_H
