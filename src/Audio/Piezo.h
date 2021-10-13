#ifndef CIRCUITOS_PIEZO_H
#define CIRCUITOS_PIEZO_H

#include <Arduino.h>

#ifdef CIRCUITOS_PIEZO_PWM
#include <driver/timer.h>

#elif defined CIRCUITOS_PIEZO_DAC
#include <driver/timer.h>
#include "soc/sens_reg.h"
#endif

class PiezoImpl {
public:
	void begin(uint8_t pin);
	uint8_t getVolume() const { return volume;}
	void setVolume(uint8_t volume) { this->volume = volume;}
	void setMute(bool mute);
	bool isMuted() const;

	void tone(uint16_t freq, uint16_t duration = 0);
	void noTone();

#ifdef CIRCUITOS_PIEZO_PWM
	static void interrupt(void* arg);
	timer_isr_handle_t timer;
#elif defined CIRCUITOS_PIEZO_DAC
	static void IRAM_ATTR timerInterrupt();
#endif

private:
	volatile uint8_t pin = -1;
	bool mute = false;
	volatile uint8_t volume = 5;

#ifdef CIRCUITOS_PIEZO_DAC
	hw_timer_t* timer = nullptr;
	const uint16_t powerHold = 2000; // How long to keep DAC powered on after last tone [ms]
	const uint16_t DACbootTime = 1000; // How long it takes DAC to power on [ms]
	volatile enum { OFF, POWERING, ON, IDLE } state = OFF;
	volatile uint32_t currentFreq = 0;
	volatile uint32_t currentDuration = 0;
	volatile uint32_t counter = 0;
#endif

};

extern PiezoImpl Piezo;

#endif //CIRCUITOS_PIEZO_H
