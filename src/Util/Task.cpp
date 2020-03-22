#include "Task.h"

Task::Task(String taskName, void (* fun)(Task*)) : taskName(taskName), func(fun){

}

Task::Task(String taskName, void (* fun)(Task*), void* arg) : taskName(taskName), func(fun), arg(arg){

}

void Task::taskFunc(void* arg){
	Task* task = static_cast<Task*>(arg);
	task->func(task);
	vTaskDelete(NULL);
}

void Task::start(){
	running = true;

	/** task function, task name, stack size, parameter, priority, handle */
	if(xTaskCreate(Task::taskFunc, taskName.c_str(), 2000, this, 0, &tHandle) != pdPASS){
		Serial.println("Task " + taskName + " start failed");
	}
}

void Task::stop(){
	running = false;
}