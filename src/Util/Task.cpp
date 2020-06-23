#include "Task.h"

#include <utility>

bool Task::pinnedTasks = false;
uint8_t Task::usedCores = 0;

Task::Task(std::string  taskName, void (* fun)(Task*), size_t stackSize, void* arg) : taskName(std::move(taskName)), func(fun), stackSize(stackSize), arg(arg){

}

void Task::taskFunc(void* arg){
	Task* task = static_cast<Task*>(arg);
	task->func(task);

	task->running = false; // in case the Task exited by itself
	task->stopped = true;

	if(pinnedTasks){
		usedCores--;
	}

	vTaskDelete(NULL);
}

void Task::start(byte priority){
	running = true;
	stopped = false;

	if(pinnedTasks){
		Serial.printf("Creating task on proc %d\n", usedCores);
		xTaskCreatePinnedToCore(Task::taskFunc, taskName.c_str(), stackSize, this, priority, &tHandle, usedCores++);
	}else{
		/** task function, task name, stack size, parameter, priority, handle */
		if(xTaskCreate(Task::taskFunc, taskName.c_str(), stackSize, this, priority, &tHandle) != pdPASS){
			Serial.printf("Task %s start failed\n", taskName.c_str());
		}
	}
}

void Task::stop(bool wait){
	running = false;

	if(wait){
		while(!stopped);
	}
}

void Task::kill(){
	if(pinnedTasks){
		usedCores--;
	}

	vTaskDelete(NULL);

	running = false;
	stopped = true;
}

void Task::setPinned(bool pinned){
	Task::pinnedTasks = pinned;
	usedCores = 0;
}

bool Task::isStopped() const{
	return stopped;
}
