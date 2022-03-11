#include "ShiftMatrixOutput.h"
#include <driver/timer.h>

#define PERIOD 1
#define LH(pin) do { digitalWrite((pin), LOW); delayMicroseconds(PERIOD); digitalWrite((pin), HIGH); delayMicroseconds(PERIOD); } while(0)
#define HL(pin) do { digitalWrite((pin), HIGH); delayMicroseconds(PERIOD); digitalWrite((pin), LOW); delayMicroseconds(PERIOD); } while(0)

ShiftMatrixOutput* ShiftMatrixOutput::instance = nullptr;

ShiftMatrixOutput::ShiftMatrixOutput(uint width, uint height) : MatrixOutput(width, height){
	instance = this;

	numShifts = ceil((float)(width * height) / 8.0f); //uses serialized 8bit shift regs
	matrixBuffer = (uint8_t*)malloc(width*height);

	timer = timerBegin(0, 80, true);
	timerAttachInterrupt(timer, timerInterrupt, true);    // P3= edge triggered
}

void ShiftMatrixOutput::init(){
	pinMode(dataPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(loadPin, OUTPUT);

	timerAlarmWrite(timer, pushInterval*1000, true); //50ms refresh interval
	timerAlarmEnable(timer);
	timerStart(timer);
}

void ShiftMatrixOutput::push(void* data){
	mutex.lock();
	memcpy(matrixBuffer, data, width*height);
	mutex.unlock();
}

void ShiftMatrixOutput::setPins(uint8_t dataPin, uint8_t clockPin, uint8_t loadPin){
	this->dataPin = dataPin;
	this->clockPin = clockPin;
	this->loadPin = loadPin;
}

void IRAM_ATTR ShiftMatrixOutput::timerInterrupt(){
	instance->pushToShift();
}

void ShiftMatrixOutput::pushToShift(){
	mutex.lock();
	//iterate by rows
	for(int i = 0; i < height; ++i){
		digitalWrite(clockPin, LOW);
		LH(loadPin);

		for(int j = 0; j < numShifts * 8; j++){
			if(i*width + j >= width*height){
				digitalWrite(dataPin, LOW);
				continue;
			}

			//column pins
			if(j >= height){
				//push data for current row to column pins
				digitalWrite(dataPin, matrixBuffer[i*width + j]);
			}else{ //row pins

				//turn on ith row, turn others off
				if(j == i){
					digitalWrite(dataPin, HIGH);
				}else{
					digitalWrite(dataPin, LOW);
				}
			}
			HL(clockPin);
		}
		delay(1);
	}
	mutex.unlock();
}
