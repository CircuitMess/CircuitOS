#include <CircuitOS.h>
#include <Util/Settings.h>

struct SettingsStruct {
	int foo;
	bool bar;
	long long unsigned chungus;
};

SettingsStruct* settings(){
	return static_cast<SettingsStruct*>(Settings::data());
}

void setup(){
	Serial.begin(115200);

	Settings::init(new SettingsStruct, sizeof(SettingsStruct));

	settings()->foo++;
	Settings::store();

	Serial.printf("Boots: %d\n", settings()->foo);
}

void loop(){

}