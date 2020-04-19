#include "Mutex.h"

Mutex::Mutex(){
	mutex = xSemaphoreCreateMutex();
}

Mutex::~Mutex(){
	vSemaphoreDelete(mutex);
}

void Mutex::lock(){
	xSemaphoreTake(mutex, portMAX_DELAY); // TODO: INCLUDE_vTaskSuspend to be set to 1
}

void Mutex::unlock(){
	xSemaphoreGive(mutex);
}
