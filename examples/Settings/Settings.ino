#include <CircuitOS.h>
#include <Util/Settings.h>
#include "Settings.h"

void setup(){
	Serial.begin(115200);
	Serial.println();

	bool exists = Settings::init(new SettingsStruct, sizeof(SettingsStruct));
	Serial.printf("Settings%s exist\n", exists ? "" : " don't");

	if(exists){
		Serial.printf("A: %d, B: %s, C: %llu\n", settings()->foo, settings()->bar ? "yay" : "nay", settings()->chungus);
	}else{
		settings()->foo = settings()->bar = settings()->chungus = 0;
	}

	settings()->foo++;
	Settings::store();

	Serial.printf("Boots: %d\n", settings()->foo);
}

void loop(){

}