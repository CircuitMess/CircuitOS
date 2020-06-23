#include "UpdateManager.h"
#include "UpdateListener.h"
#include "../Util/Debug.h"

Task UpdateManager::task("UpdateManager", UpdateManager::taskFunc, 10000);
Vector<UpdateListener*> UpdateManager::listeners;
uint UpdateManager::lastMillis = millis();

void UpdateManager::startTask(byte priority){
	task.start(priority);
}

void UpdateManager::setStackSize(size_t size){
	if(task.running){
		task.stop(true);
	}

	task = Task("UpdateManager", UpdateManager::taskFunc, size);
}

void UpdateManager::addListener(UpdateListener* listener){
	listeners.push_back(listener);
}

void UpdateManager::removeListener(UpdateListener* listener){
	uint index = listeners.indexOf(listener);
	if(index == -1) return;
	listeners.remove(index);
}

void UpdateManager::taskFunc(Task* task){
	logln("UpdateManager started in task mode");

	while(task->running){
		if(listeners.empty()){
			vTaskDelay(1);
		}else{
			update();
		}
	}
}

void UpdateManager::update(){
	uint m = micros();
	uint delta = m - lastMillis;

	for(UpdateListener* listener : listeners){
		listener->update(delta);
	}

	lastMillis = m;
}
