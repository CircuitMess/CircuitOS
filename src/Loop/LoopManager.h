#ifndef CIRCUITOS_LOOPMANAGER_H
#define CIRCUITOS_LOOPMANAGER_H

#include <Arduino.h>
#include <unordered_set>
#include "../../Setup.hpp"
#include <functional>

class LoopListener;
class Task;

class LoopManager {
public:
	/**
	 * Reserve listener vector slots.
	 * @param count Expected listener count
	 */
	static void reserve(size_t count);

	static void addListener(LoopListener* listener);
	static void removeListener(LoopListener* listener);

	static void loop();

	static void resetTime();

	/**
	 * Run later. The function will be ran after the next loop iteration is completed.
	 */
	static void defer(std::function<void(uint32_t)>);

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

	static std::vector<std::function<void(uint32_t)>> deferred;

#ifdef CIRCUITOS_TASK
	static Task* task;
#endif

};


#endif //CIRCUITOS_LOOPMANAGER_H
