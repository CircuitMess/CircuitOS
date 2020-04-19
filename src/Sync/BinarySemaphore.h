#ifndef CIRCUITOS_BINARYSEMAPHORE_H
#define CIRCUITOS_BINARYSEMAPHORE_H

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

class BinarySemaphore {
	BinarySemaphore();
	~BinarySemaphore();

	void wait();
	void signal();

private:
	SemaphoreHandle_t mutex;
};


#endif //CIRCUITOS_BINARYSEMAPHORE_H
