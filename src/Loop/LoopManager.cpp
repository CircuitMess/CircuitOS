#include "LoopManager.h"
#include "LoopListener.h"

#ifdef CIRCUITOS_TASK
#include "../Util/Task.h"
#include "../Util/Debug.h"

Task* LoopManager::task = nullptr;
#endif

std::unordered_set<LoopListener*> LoopManager::listeners;
uint LoopManager::lastMicros = micros();


void LoopManager::loop(){
	uint m = micros();
	uint delta = m - lastMicros;

	auto listenersCopy(listeners);
	for(auto listener : listenersCopy){
		listener->loop(delta);
	}

	//if any listeners have called LoopManager::loop(), the recursion will have set lastMicros to a newer value by now
	if(lastMicros < m){
		//no recursion has occured
		lastMicros = m;
	}
}

void LoopManager::addListener(LoopListener* listener){
	listeners.insert(listener);
}

void LoopManager::removeListener(LoopListener* listener){
	listeners.erase(listener);
}

#ifdef CIRCUITOS_TASK
void LoopManager::startTask(byte priority, byte core){
	if(task == nullptr){
		task = new Task("LoopManager", LoopManager::taskFunc, 10000);
	}

	task->start(priority, core);
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