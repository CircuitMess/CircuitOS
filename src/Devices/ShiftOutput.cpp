#include "ShiftOutput.h"

#define PERIOD 1
#define LH(pin) do { digitalWrite(pin, LOW); digitalWrite(pin, HIGH); } while(0)
#define HL(pin) do { digitalWrite(pin, HIGH); digitalWrite(pin, LOW); } while(0)

const float ShiftOutput::nopCycles = (float) ESP.getCpuFreqMHz() / 3.0f;

ShiftOutput::ShiftOutput(uint8_t clk, const std::vector<uint8_t>& dataPins) : clockPin(clk), dataPins(dataPins), size(dataPins.size()){
	state.resize(size);
}

ShiftOutput::ShiftOutput(uint8_t clockPin, uint8_t dataPin) : ShiftOutput(clockPin, std::vector<uint8_t>{ dataPin }){

}

void ShiftOutput::begin(){
	pinMode(clockPin, OUTPUT);
	digitalWrite(clockPin, LOW);

	for(auto data : this->dataPins){
		pinMode(data, OUTPUT);
	}

	send(this->state);
}

void ShiftOutput::set(uint16_t _pin, bool state){
	uint8_t pin = _pin % 8;
	uint8_t index = (_pin - pin) / 8;

	set(index, pin, state);
}

void ShiftOutput::set(uint8_t index, uint8_t pin, bool state){
	if(index >= size || pin >= 8) return;

	this->state[index][pin] = state;

	send(this->state);
}

void ShiftOutput::set(uint8_t index, const std::array<bool, 8>& state){
	if(index >= size) return;

	this->state[index] = state;

	send(this->state);
}

void ShiftOutput::set(const std::vector<std::array<bool, 8>>& state){
	if(state.size() != size) return;

	this->state = state;

	send(this->state);
}

void ShiftOutput::setAll(bool state){
	for(auto& shift : this->state){
		shift.fill(state);
	}

	send(this->state);
}

void IRAM_ATTR ShiftOutput::send(const std::vector<std::array<bool, 8>>& state){
	digitalWrite(clockPin, LOW);

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < size; j++){
			if(state[j][7 - i]){
				GPIO.out_w1ts = ((uint32_t) 1) << dataPins[j];
			}else{
				GPIO.out_w1tc = ((uint32_t) 1) << dataPins[j];
			}
		}

		HL(clockPin);
	}
}

bool ShiftOutput::get(uint16_t _pin){
	uint8_t pin = _pin % 8;
	uint8_t index = (_pin - pin) / 8;

	return get(index, pin);
}

bool ShiftOutput::get(uint8_t index, uint8_t pin){
	if(index >= size || pin >= 8) return false;
	return state[index][pin];
}

std::array<bool, 8> ShiftOutput::get(uint8_t index){
	if(index >= size) return { };
	return state[index];
};

std::vector<std::array<bool, 8>> ShiftOutput::get(){
	return state;
}

void IRAM_ATTR ShiftOutput::delayNanos(uint32_t nanos){
	uint32_t cycles = round((float) nanos / nopCycles);
	for(volatile uint32_t i = 0; i < cycles; i++);
}
