#ifndef CIRCUITOS_UPDATEMANAGER_H
#define CIRCUITOS_UPDATEMANAGER_H


#include "../Util/Vector.h"
#include "../Setup.hpp"

class UpdateListener;
class Task;

class UpdateManager {
public:

	static void addListener(UpdateListener* listener);
	static void removeListener(UpdateListener* listener);

	static void update();

#ifdef CIRCUITOS_TASK
	/**
	 * Start the UpdateManager as a separate task. The default stack size for the task is 10kb.
	 * @see UpdateManager::setStackSize
	 * @param priority
	 */
	static void startTask(byte priority = 0);

	/**
	 * Stops the UpdateManager task.
	 */
	static void stopTask();

	/**
	 * Set the stack size for the UpdateManager task. Applicable only when running in a separate task, and will stop
	 * the task if it's running.
	 * @see UpdateManager::startTask
	 * @param size Stack size in bytes.
	 */
	static void setStackSize(size_t size);

	static void taskFunc(Task* task);
#endif

private:
	static Vector<UpdateListener*> listeners;
	static uint lastMicros;

#ifdef CIRCUITOS_TASK
	static Task* task;
#endif

};


#endif //CIRCUITOS_UPDATEMANAGER_H
