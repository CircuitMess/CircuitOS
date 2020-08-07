#ifndef CIRCUITOS_PIEZO_H
#define CIRCUITOS_PIEZO_H

#include <Arduino.h>

class PiezoImpl {
public:
	void begin(uint8_t pin);

	void setMute(bool mute);
	bool isMuted() const;

	void tone(uint16_t freq, uint16_t duration = 0);
	void noTone();

private:
	uint8_t pin = -1;
	bool mute = false;

};

extern PiezoImpl Piezo;

#endif //CIRCUITOS_PIEZO_H
