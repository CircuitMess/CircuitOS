#ifndef CIRCUITOS_BINARYSEMAPHORE_H
#define CIRCUITOS_BINARYSEMAPHORE_H

#define INCLUDE_vTaskSuspend 1
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

class BinarySemaphore {
public:
	BinarySemaphore();
	~BinarySemaphore();

	bool wait();
	void signal();

private:
	SemaphoreHandle_t semaphore;
};


#endif //CIRCUITOS_BINARYSEMAPHORE_H
