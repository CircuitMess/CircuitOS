#include "BinarySemaphore.h"

BinarySemaphore::BinarySemaphore(){
	mutex = xSemaphoreCreateBinary();
}

BinarySemaphore::~BinarySemaphore(){
	vSemaphoreDelete(mutex);
}

bool BinarySemaphore::wait(){
	return xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE; // TODO: INCLUDE_vTaskSuspend to be set to 1
}

void BinarySemaphore::signal(){
	xSemaphoreGive(mutex);
}
