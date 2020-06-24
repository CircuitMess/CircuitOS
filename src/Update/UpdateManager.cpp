#include "UpdateManager.h"
#include "UpdateListener.h"

#ifdef CIRCUITOS_TASK
#include <Util/Task.h>
#include "../Util/Debug.h"

Task* UpdateManager::task = nullptr;
#endif

Vector<UpdateListener*> UpdateManager::listeners;
uint UpdateManager::lastMicros = micros();

void UpdateManager::addListener(UpdateListener* listener){
	listeners.push_back(listener);
}

void UpdateManager::removeListener(UpdateListener* listener){
	uint index = listeners.indexOf(listener);
	if(index == -1) return;
	listeners.remove(index);
}

void UpdateManager::update(){
	uint m = micros();
	uint delta = m - lastMicros;

	for(UpdateListener* listener : listeners){
		listener->update(delta);
	}

	lastMicros = m;
}

#ifdef CIRCUITOS_TASK
void UpdateManager::startTask(byte priority){
	if(task == nullptr){
		task = new Task("UpdateManager", UpdateManager::taskFunc, 10000);
	}

	task->start(priority);
}

void UpdateManager::stopTask(){
	if(task == nullptr) return;
	task->stop(true);

}

void UpdateManager::setStackSize(size_t size){
	if(task != nullptr){
		task->stop(true);
		delete task;
	}

	task = new Task("UpdateManager", UpdateManager::taskFunc, size);
}

void UpdateManager::taskFunc(Task* task){
	logln("UpdateManager started in task mode");

	while(task->running){
		vTaskDelay(1);
		update();
	}
}
#endif