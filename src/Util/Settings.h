#ifndef CIRCUITOS_SETTINGS_H
#define CIRCUITOS_SETTINGS_H

#include <Arduino.h>
#include <nvs.h>

#ifndef nvs_handle_t
typedef nvs_handle nvs_handle_t;
#endif

class Settings {
public:
	static void init(void* ptr, size_t size);

	static void store();
	static void retrieve();

	static void* data();

private:
	static void* _data;
	static size_t dataSize;
	static nvs_handle_t handle;
};

#endif //CIRCUITOS_SETTINGS_H
