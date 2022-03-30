#include <cstdlib>
#include "DelayedMatrixOutput.h"
#include "../../Loop/LoopManager.h"

DelayedMatrixOutput::DelayedMatrixOutput(MatrixOutput* out, uint32_t pushDelay) :
		MatrixOutput(out->getWidth(), out->getHeight()), out(out), pushDelay(pushDelay), data(out->getWidth(), out->getHeight()){

}

void DelayedMatrixOutput::init(){
	LoopManager::addListener(this);
}

void DelayedMatrixOutput::push(const MatrixPixelData& data){
	if(millis() - lastPush >= pushDelay){
		out->push(data);
		lastPush = millis();
	} else {
		this->data = data;
		pushNeeded = true;
	}
}

void DelayedMatrixOutput::loop(uint micros){
	if(pushNeeded && millis() - lastPush > pushDelay){
		lastPush = millis();
		out->push(data);
		pushNeeded = false;
	}
}
