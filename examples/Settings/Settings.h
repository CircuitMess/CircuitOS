#include <Util/Settings.h>

struct SettingsStruct {
	int foo;
	bool bar;
	long long unsigned chungus;
};

SettingsStruct* settings(){
	return static_cast<SettingsStruct*>(Settings::data());
}