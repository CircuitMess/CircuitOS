#include "LoopManager.h"
#include "LoopListener.h"

#ifdef CIRCUITOS_TASK
#include "../Util/Task.h"
#include "../Util/Debug.h"

Task* LoopManager::task = nullptr;
#endif

std::unordered_set<LoopListener*> LoopManager::listeners;
std::unordered_set<LoopListener*> LoopManager::addedListeners;
std::unordered_set<LoopListener*> LoopManager::removedListeners;
uint LoopManager::lastMicros = 0;
volatile bool LoopManager::iterating = false;

void LoopManager::reserve(size_t count){
	listeners.reserve(count);
	addedListeners.reserve(count);
	removedListeners.reserve(count);
}

void LoopManager::addListener(LoopListener* listener){
	if(!iterating){
		listeners.insert(listener);
		addedListeners.erase(listener);
		removedListeners.erase(listener);
		return;
	}

	// Check if queued for removing
	if(removedListeners.find(listener) != removedListeners.end()){
		removedListeners.erase(listener);
	}

	// Skip if already added
	if(listeners.find(listener) != listeners.end()) return;

	addedListeners.insert(listener);
}

void LoopManager::removeListener(LoopListener* listener){
	if(!iterating){
		listeners.erase(listener);
		addedListeners.erase(listener);
		removedListeners.erase(listener);
		return;
	}

	// Check if queued for adding
	if(addedListeners.find(listener) != addedListeners.end()){
		addedListeners.erase(listener);
	}

	// Skip if not added
	if(listeners.find(listener) == listeners.end()) return;

	removedListeners.insert(listener);
}

void LoopManager::loop(){
	if(iterating){
		return;
	}

	iterating = true;

	uint lastMicros = LoopManager::lastMicros;
	uint m = micros();
	uint delta = m - lastMicros;
	if(lastMicros == 0){
		delta = 0;
	}

	for(auto listener : listeners){
		if(removedListeners.find(listener) != removedListeners.end()){
			continue;
		}
		listener->loop(delta);
	}

	clearListeners();
	insertListeners();

	iterating = false;
	if(LoopManager::lastMicros == lastMicros){
		LoopManager::lastMicros = m;
	}
}

void LoopManager::insertListeners(){
	listeners.insert(addedListeners.begin(), addedListeners.end());
	addedListeners.clear();
}

void LoopManager::clearListeners(){
	for(const auto& listener : removedListeners){
		listeners.erase(listener);
	}

	removedListeners.clear();
}

void LoopManager::resetTime(){
	lastMicros = micros();
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