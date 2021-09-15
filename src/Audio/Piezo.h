#ifndef CIRCUITOS_PIEZO_H
#define CIRCUITOS_PIEZO_H

#include <Arduino.h>

#ifdef CIRCUITOS_PIEZO_ESP32
#include <driver/timer.h>
#endif

class PiezoImpl {
public:
	void begin(uint8_t pin);

	void setMute(bool mute);
	bool isMuted() const;

	void tone(uint16_t freq, uint16_t duration = 0);
	void noTone();

#ifdef CIRCUITOS_PIEZO_ESP32
	static void interrupt(void* arg);
	timer_isr_handle_t timer;
#endif

private:
	uint8_t pin = -1;
	bool mute = false;

};

extern PiezoImpl Piezo;

#endif //CIRCUITOS_PIEZO_H
