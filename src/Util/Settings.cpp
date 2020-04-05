#include "Settings.h"

void* Settings::_data = nullptr;
size_t Settings::dataSize = 0;
uint Settings::handle = 0;

void Settings::init(void* ptr, size_t size){
	_data = ptr;
	dataSize = size;

	esp_err_t err = nvs_open("CircuitOS", NVS_READWRITE, &handle);
	if(err != ESP_OK){
		Serial.printf("Non-volatile storage initialization error: %d\n", err);
	}

	retrieve();
}

void* Settings::data(){
	return _data;
}

void Settings::store(){
	esp_err_t err = nvs_set_blob(handle, "foo", _data, dataSize);

	if(err != ESP_OK){
		Serial.println("Non-volatile storage store error: %d");
	}
}

void Settings::retrieve(){
	esp_err_t err = nvs_get_blob(handle, "foo", _data, &dataSize);

	if(err != ESP_OK){
		Serial.println("Non-volatile storage retrieval error: %d");
	}
}