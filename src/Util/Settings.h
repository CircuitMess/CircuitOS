#ifndef CIRCUITOS_SETTINGS_H
#define CIRCUITOS_SETTINGS_H

#include <Arduino.h>

#ifdef CIRCUITOS_NVS
#include <nvs.h>

#ifndef nvs_handle_t
typedef nvs_handle nvs_handle_t;
#endif
#endif

class Settings {
public:
	/**
	 * Initializes the settings
	 * @param ptr Pointer to the data structure to be used
	 * @param size Size of the structure
	 * @return Whether any settings are already saved on the device
	 */
	static bool init(void* ptr, size_t size);

	static void store();
	static void retrieve();

	static void* data();

private:
	static void* _data;
	static size_t dataSize;

#ifdef CIRCUITOS_NVS
	static nvs_handle_t handle;
#endif

};

#endif //CIRCUITOS_SETTINGS_H
