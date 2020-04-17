
#include <Arduino.h>
#include <CircuitOS.h>
#include <Sync/Mutex.h>
#include <Util/Task.h>

void loop_task(Task* task);

Mutex mutex;
Task task("OtherTask", loop_task);

void setup(){
	Serial.begin(115200);
	task.start();
}

void loop(){
	Serial.println("Task 1 trying to enter critical section");
	mutex.lock();
	Serial.println("Task 1 entered");
	usleep(1000 * (2000 + rand() % 1000));
	Serial.println("Task 1 exiting critical section");
	mutex.unlock();
	usleep(1000 * (2000 + rand() % 1000));
}

void loop_task(Task* task){
	while(task->running){
		Serial.println("Task 2 trying to enter critical section");
		mutex.lock();
		Serial.println("Task 2 entered");
		usleep(1000 * (2000 + rand() % 1000));
		Serial.println("Task 2 exiting critical section");
		mutex.unlock();
		usleep(1000 * (2000 + rand() % 1000));
	}
}