#include "Task.h"

#include <utility>

Task::Task(std::string  taskName, void (* fun)(Task*), size_t stackSize, void* arg) : taskName(std::move(taskName)), func(fun), stackSize(stackSize), arg(arg){

}

void Task::taskFunc(void* arg){
	Task* task = static_cast<Task*>(arg);
	task->func(task);
	vTaskDelete(NULL);
}

void Task::start(){
	running = true;

	/** task function, task name, stack size, parameter, priority, handle */
	if(xTaskCreate(Task::taskFunc, taskName.c_str(), stackSize, this, 0, &tHandle) != pdPASS){
		Serial.printf("Task %s start failed\n", taskName.c_str());
	}
}

void Task::stop(){
	running = false;
}