#include "RTC.h"

RTC::RTC(){
	if(!RTC_PCF8523::begin()){
		Serial.println("RTC init error");
	}
}
