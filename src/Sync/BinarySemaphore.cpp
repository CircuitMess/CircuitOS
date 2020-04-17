#include "BinarySemaphore.h"

BinarySemaphore::BinarySemaphore(){
	mutex = xSemaphoreCreateBinary();
}

BinarySemaphore::~BinarySemaphore(){
	vSemaphoreDelete(mutex);
}

void BinarySemaphore::wait(){
	xSemaphoreTake(mutex, portMAX_DELAY); // TODO: INCLUDE_vTaskSuspend to be set to 1
}

void BinarySemaphore::signal(){
	xSemaphoreGive(mutex);
}
