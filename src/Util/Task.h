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
	 * Start the task with optional priority. When a CPU sore becomes available, and more than one task is waiting, the
	 * one with higher priority will be picked. This can to starvation if there are more tasks waiting for execution.
	 *
	 * @see configUSETIMESLICING prevents the scheduler switching between tasks of equal priority when a tick interrupt fires (every 1ms by default - FreeRTOS tick rate)
	 *
	 * @param priority
	 */
	void start(byte priority = 0 /*(1 | portPRIVILEGE_BIT)*/, int8_t core = -1);

	/**
	 * Stop the task gracefully. The task will stop when the current iteration of the loop finishes.
	 * @param wait Whether to wait for the task to finish.
	 */
	void stop(bool wait = false);

	/**
	 * Stops the task immediately. In other words, kills it.
	 */
	void kill();

	/**
	 * Core pinning. If set to true, each new task will be pinned to a new core. Call again to reset assignment.
	 * @param pinned
	 */
	static void setPinned(bool pinned);

	bool running = false;
	void* arg = nullptr;

	static void taskFunc(void* arg);

	/**
	 * Whether the task is stopped.
	 * @return
	 */
	bool isStopped() const;

private:
	std::string taskName;
	void (*func)(Task*) = nullptr;
	size_t stackSize = 2048;

	TaskHandle_t tHandle;

	static bool pinnedTasks;
	static uint8_t usedCores;

	bool stopped = true;
};


#endif //CIRCUITOS_TASK_H
