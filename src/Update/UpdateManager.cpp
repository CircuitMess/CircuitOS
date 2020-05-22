#include "UpdateManager.h"
#include "../Util/Debug.h"

Task UpdateManager::task("UpdateManager", UpdateManager::taskFunc);
Vector<UpdateListener*> UpdateManager::listeners;
uint UpdateManager::lastMillis = millis();

void UpdateManager::startTask(){
	task.start();
	logln("UpdateManager started in task mode");
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
	logln("UpdateManager started");

	while(task->running){
		vTaskDelay(1);
		update();
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
