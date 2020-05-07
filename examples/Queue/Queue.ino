#include <Arduino.h>
#include <CircuitOS.h>
#include <Sync/Queue.h>
#include <Util/Task.h>

void loop_task(Task* task);
Task task("OtherTask", loop_task);

Queue queue(10, sizeof(byte));
byte message = 0x01;

void setup(){
	Serial.begin(115200);
	Serial.println();

	Serial.println("Posting 3 messages to queue");
	queue.send(&message);
	queue.send(&message);
	queue.send(&message);

	task.start();
}

void loop(){
	delay(2000 + rand() % 1000);

	Serial.println("-> Posting message to queue");
	delay(5);
	queue.send(&message);
}

void loop_task(Task* task){
	while(task->running){
		Serial.println("-- Reading message from queue");
		delay(5);

		queue.receive(&message);

		Serial.printf("<- Message read, %d left\n", queue.count());

		delay(200);
	}
}