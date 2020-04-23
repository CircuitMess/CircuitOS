#ifndef CIRCUITOS_MUTEX_H
#define CIRCUITOS_MUTEX_H

#define INCLUDE_vTaskSuspend 1
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

class Mutex {
public:
	Mutex();
	~Mutex();

	bool lock();
	void unlock();

private:
	SemaphoreHandle_t mutex;
};


#endif //CIRCUITOS_MUTEX_H
