#include "Mutex.h"

Mutex::Mutex(){
	mutex = xSemaphoreCreateMutex();
}

Mutex::~Mutex(){
	vSemaphoreDelete(mutex);
}

bool Mutex::lock(){
	return xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE; // TODO: INCLUDE_vTaskSuspend to be set to 1
}

void Mutex::unlock(){
	xSemaphoreGive(mutex);
}
