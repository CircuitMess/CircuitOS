#include "ICMU20948.h"
#include <Wire.h>

ICMU20948::ICMU20948(){
	Wire.begin(21, 22);
}

void ICMU20948::begin(){
	byte buffer;
	Wire.beginTransmission(ADDR);
	Wire.write(addr.WHO_AM_I);
	Wire.endTransmission(I2C_NOSTOP);
	Wire.requestFrom(ADDR, 1);
	int i;
	while((i = Wire.available())){
		Serial.printf("Reading %d bytes\n", i);
		buffer = Wire.read();
	}
	Serial.printf("Device is %hhx\n", buffer);
}
