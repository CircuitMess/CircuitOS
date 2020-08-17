#include "LoopListener.h"
#include "LoopManager.h"

#ifdef CIRCUITOS_TASK
#include <Util/Task.h>
#include <utility>
#endif

LoopListener::LoopListener(){
	// LoopManager::addListener(this);
}

LoopListener::~LoopListener(){
	LoopManager::removeListener(this);
}

#ifdef CIRCUITOS_TASK
void LoopListener::startTask(std::string name, byte priority, size_t stackSize){
	lastMicros = micros();
	task = new Task(std::move(name), taskFunc, stackSize, this);
	task->start(priority);
}

void LoopListener::stopTask(){
	if(task == nullptr || !task->running) return;
	task->stop(true);
	delete task;
	task = nullptr;
}

void LoopListener::taskFunc(Task* task){
	LoopListener* instance = static_cast<LoopListener*>(task->arg);

	while(task->running){
		vTaskDelay(1);

		uint m = micros();
		uint delta = m - instance->lastMicros;

		instance->update(delta);

		instance->lastMicros = m;
	}
}
#endif