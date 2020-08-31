#include "LoopManager.h"
#include "LoopListener.h"

#ifdef CIRCUITOS_TASK
#include <Util/Task.h>
#include "../Util/Debug.h"

Task* LoopManager::task = nullptr;
#endif

Vector<LoopListener*> LoopManager::listeners;
uint LoopManager::lastMicros = micros();

void LoopManager::addListener(LoopListener* listener){
	listeners.push_back(listener);
}

void LoopManager::removeListener(LoopListener* listener){
	uint index = listeners.indexOf(listener);
	if(index == -1) return;
	listeners.remove(index);
}

void LoopManager::loop(){
	uint m = micros();
	uint delta = m - lastMicros;

	for(LoopListener* listener : listeners){
		listener->loop(delta);
	}

	lastMicros = m;
}

#ifdef CIRCUITOS_TASK
void LoopManager::startTask(byte priority){
	if(task == nullptr){
		task = new Task("LoopManager", LoopManager::taskFunc, 10000);
	}

	task->start(priority);
}

void LoopManager::stopTask(){
	if(task == nullptr) return;
	task->stop(true);

}

void LoopManager::setStackSize(size_t size){
	if(task != nullptr){
		task->stop(true);
		delete task;
	}

	task = new Task("LoopManager", LoopManager::taskFunc, size);
}

void LoopManager::taskFunc(Task* task){
	logln("LoopManager started in task mode");

	while(task->running){
		vTaskDelay(1);
		loop();
	}
}
#endif