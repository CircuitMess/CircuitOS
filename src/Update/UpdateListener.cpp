#include "UpdateListener.h"
#include "UpdateManager.h"

#ifdef CIRCUITOS_TASK
#include <Util/Task.h>
#include <utility>
#endif

UpdateListener::UpdateListener(){
	// UpdateManager::addListener(this);
}

UpdateListener::~UpdateListener(){
	UpdateManager::removeListener(this);
}

#ifdef CIRCUITOS_TASK
void UpdateListener::startTask(std::string name, byte priority, size_t stackSize){
	lastMicros = micros();
	task = new Task(std::move(name), taskFunc, stackSize, this);
	task->start(priority);
}

void UpdateListener::stopTask(){
	if(task == nullptr || !task->running) return;
	task->stop(true);
	delete task;
	task = nullptr;
}

void UpdateListener::taskFunc(Task* task){
	UpdateListener* instance = static_cast<UpdateListener*>(task->arg);

	while(task->running){
		vTaskDelay(1);

		uint m = micros();
		uint delta = m - instance->lastMicros;

		instance->update(delta);

		instance->lastMicros = m;
	}
}
#endif