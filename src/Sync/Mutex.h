#ifndef CIRCUITOS_MUTEX_H
#define CIRCUITOS_MUTEX_H

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

class Mutex {
public:
	Mutex();
	~Mutex();

	void lock();
	void unlock();

private:
	SemaphoreHandle_t mutex;
};


#endif //CIRCUITOS_MUTEX_H
