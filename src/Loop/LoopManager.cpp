#include "LoopManager.h"
#include "LoopListener.h"

#ifdef CIRCUITOS_TASK
#include "../Util/Task.h"
#include "../Util/Debug.h"

Task* LoopManager::task = nullptr;
#endif

std::unordered_set<LoopListener*> LoopManager::listeners;
std::unordered_set<LoopListener*> LoopManager::removedListeners;
uint LoopManager::lastMicros = micros();

void LoopManager::addListener(LoopListener* listener){
	if(listeners.find(listener) == listeners.end()){
		listeners.insert(listener);
	}

	auto l = removedListeners.find(listener);
	if(l != removedListeners.end()){
		removedListeners.erase(l);
	}
}

void LoopManager::removeListener(LoopListener* listener){
	if(listeners.find(listener) == listeners.end() || removedListeners.find(listener) != removedListeners.end()) return;
	removedListeners.insert(listener);
}

void LoopManager::loop(){
	uint m = micros();
	uint delta = m - lastMicros;
	clearListeners();

	for(auto listener : listeners){
		if(removedListeners.find(listener) != removedListeners.end()){
			continue;
		}
		listener->loop(delta);
	}

	clearListeners();
	lastMicros = m;
}

void LoopManager::clearListeners(){
	for(const auto& listener : removedListeners){
		listeners.erase(listener);
	}
	if(!removedListeners.empty()){
		removedListeners.clear();
	}
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