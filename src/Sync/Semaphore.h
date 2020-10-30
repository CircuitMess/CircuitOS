#ifndef CIRCUITOS_SEMAPHORE_H
#define CIRCUITOS_SEMAPHORE_H

#define INCLUDE_vTaskSuspend 1
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

class Semaphore {
public:
	Semaphore(uint size);
	~Semaphore();

	bool wait();
	void signal();

private:
	SemaphoreHandle_t semaphore;
};


#endif //CIRCUITOS_SEMAPHORE_H
