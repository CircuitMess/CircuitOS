#ifndef CIRCUITOS_TASK_H
#define CIRCUITOS_TASK_H

#include <Arduino.h>
#include <freertos/task.h>
#include <string>

class Task {
public:

	/**
	 *
	 * @param taskName For debugging purposes
	 * @param fun Task function
	 */
	Task(std::string  taskName, void (*fun)(Task*), size_t stackSize = 2048, void* arg = nullptr);

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
	std::string taskName;
	void (*func)(Task*) = nullptr;
	size_t stackSize = 2048;

	TaskHandle_t tHandle;
};


#endif //CIRCUITOS_TASK_H
