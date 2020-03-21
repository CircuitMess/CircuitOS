#ifndef CIRCUITOS_TASK_H
#define CIRCUITOS_TASK_H

#include <Arduino.h>
#include <freertos/task.h>

class Task {
public:

	/**
	 *
	 * @param taskName For debugging purposes
	 * @param fun Task function
	 */
	Task(String taskName, void (*fun)(Task*));
	Task(String taskName, void (*fun)(Task*), void* arg);

	/**
	 * Start the task.
	 */
	void start();

	/**
	 * Terminate the task.
	 */
	void stop();

	bool running = false;
	void* arg = nullptr;

	static void taskFunc(void* arg);

private:

	String taskName;
	void (*func)(Task*) = nullptr;
	TaskHandle_t tHandle;
};


#endif //CIRCUITOS_TASK_H
