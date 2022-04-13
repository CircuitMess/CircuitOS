#ifndef CIRCUITOS_SHIFTOUTPUT_H
#define CIRCUITOS_SHIFTOUTPUT_H

#include <Arduino.h>
#include <vector>
#include <array>

class ShiftOutput {
public:
	ShiftOutput(uint8_t clockPin, const std::vector<uint8_t>& dataPins);
	ShiftOutput(uint8_t clockPin, uint8_t dataPin);

	void begin();

	void set(uint16_t pin, bool state);
	void set(uint8_t index, uint8_t pin, bool state);
	void set(uint8_t index, const std::array<bool, 8>& state);
	void set(const std::vector<std::array<bool, 8>>& state);
	void setAll(bool state);

	bool get(uint16_t pin);
	bool get(uint8_t index, uint8_t pin);
	std::array<bool, 8> get(uint8_t index);
	std::vector<std::array<bool, 8>> get();

	static void IRAM_ATTR delayNanos(uint32_t nanos);

private:
	const uint8_t clockPin;
	const std::vector<uint8_t> dataPins;
	const uint8_t size;

	std::vector<std::array<bool, 8>> state;

	static const float nopCycles;

public:
	void IRAM_ATTR send(const std::vector<std::array<bool, 8>>& newState);

};


#endif //CIRCUITOS_SHIFTOUTPUT_H
