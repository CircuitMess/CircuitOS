#ifndef CIRCUITOS_ICMU20948_H
#define CIRCUITOS_ICMU20948_H


#include <Arduino.h>

const struct PROGMEM {
	byte WHO_AM_I = 0;
} addr;

#define ADDR 68
#define I2C_NOSTOP (1 << 4)

class ICMU20948 {
public:
	ICMU20948();
	void begin();

private:

};


#endif //CIRCUITOS_ICMU20948_H
