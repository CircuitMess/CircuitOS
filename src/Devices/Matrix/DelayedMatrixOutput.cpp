#include <cstdlib>
#include "DelayedMatrixOutput.h"
#include "../../Loop/LoopManager.h"

DelayedMatrixOutput::DelayedMatrixOutput(MatrixOutput* out, uint32_t pushDelay) :
		MatrixOutput(out->getWidth(), out->getHeight()), out(out), pushDelay(pushDelay){

}

void DelayedMatrixOutput::init(){
	lastPush = millis();
	LoopManager::addListener(this);
}

void DelayedMatrixOutput::push(const MatrixPixelData& data){
	if(millis() - lastPush >= pushDelay){
		lastPush = millis();
		out->push(data);
		pushNeeded = false;
		delete this->data;
		this->data = nullptr;

	}else{
		pushNeeded = true;
		delete this->data;
		this->data = new MatrixPixelData(data);
	}
}

void DelayedMatrixOutput::loop(uint micros){
	if(pushNeeded && millis() - lastPush > pushDelay){
		lastPush = millis();
		out->push(*data);
		pushNeeded = false;
		delete data;
		data = nullptr;
	}

}
