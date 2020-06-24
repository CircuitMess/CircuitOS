#ifndef CIRCUITOS_UPDATELISTENER_H
#define CIRCUITOS_UPDATELISTENER_H

#include <Arduino.h>
#include "../Setup.hpp"

#ifdef CIRCUITOS_TASK
#include <string>

class Task;
#endif

class UpdateListener {
public:
	UpdateListener();
	virtual ~UpdateListener();

	virtual void update(uint micros) = 0;

#ifdef CIRCUITOS_TASK
	void startTask(std::string name, byte priority = 0, size_t stackSize = 2048);
	void stopTask();
	static void taskFunc(Task* task);
#endif

private:

#ifdef CIRCUITOS_TASK
	Task* task = nullptr;
	uint lastMicros = 0;
#endif

};


#endif //CIRCUITOS_UPDATELISTENER_H
