#ifndef CIRCUITOS_LOOPMANAGER_H
#define CIRCUITOS_LOOPMANAGER_H

#include <Arduino.h>
#include <unordered_set>
#include "../../Setup.hpp"

class LoopListener;
class Task;

class LoopManager {
public:

	static void addListener(LoopListener* listener);
	static void removeListener(LoopListener* listener);

	static void loop();

	static void resetTime();

#ifdef CIRCUITOS_TASK
	/**
	 * Start the LoopManager as a separate task. The default stack size for the task is 10kb.
	 * @see LoopManager::setStackSize
	 * @param priority
	 */
	static void startTask(byte priority = 0, byte core = 1);

	/**
	 * Stops the LoopManager task.
	 */
	static void stopTask();

	/**
	 * Set the stack size for the LoopManager task. Applicable only when running in a separate task, and will stop
	 * the task if it's running.
	 * @see LoopManager::startTask
	 * @param size Stack size in bytes.
	 */
	static void setStackSize(size_t size);

	static void taskFunc(Task* task);
#endif

private:
	static std::unordered_set<LoopListener*> listeners;
	static std::unordered_set<LoopListener*> addedListeners;
	static std::unordered_set<LoopListener*> removedListeners;

	volatile static bool iterating;
	static uint lastMicros;
	static void insertListeners();
	static void clearListeners();

#ifdef CIRCUITOS_TASK
	static Task* task;
#endif

};


#endif //CIRCUITOS_LOOPMANAGER_H
