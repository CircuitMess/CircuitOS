#include <Arduino.h>
#include <CircuitOS.h>
#include <Time.h>
#include <RTC/RTC.h>

RTC rtc;

char buffer[50];
DateTime timenow;

void setup(){
	Serial.begin(115200);

	// TODO: check this

	// Adjust the RTC to a time
	// Do this once, when setting the time and date
	rtc.adjust(DateTime(2020, 4, 2, 10, 10, 0));

	// Set internal clock time to RTC time
	// Do this in setup()
	setTime(rtc.now().secondstime());
}

void loop(){
	// Time is fetched from the internal clock
	timenow = now();

	strcpy(buffer, "YYYY-MM-DD hh:mm:ss");
	timenow.toString(buffer);
	Serial.printf("Date: %s\n", buffer);
	delay(1000);
}