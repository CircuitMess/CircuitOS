#include <CircuitOS.h>
#include <Util/Settings.h>
#include "Settings.h"

void setup(){
	Serial.begin(115200);

	Settings::init(new SettingsStruct, sizeof(SettingsStruct));

	settings()->foo++;
	Settings::store();

	Serial.printf("Boots: %d\n", settings()->foo);
}

void loop(){

}