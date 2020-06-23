#ifndef CIRCUITOS_UPDATEMANAGER_H
#define CIRCUITOS_UPDATEMANAGER_H


#include "../Util/Vector.h"
#include "../Util/Task.h"

class UpdateListener;

class UpdateManager {
public:

	/**
	 * Start the UpdateManager as a separate task. The default stack size for the task is 10kb.
	 * @see UpdateManager::setStackSize
	 * @param priority
	 */
	static void startTask(byte priority);

	/**
	 * Set the stack size for the UpdateManager task. Applicable only when running in a separate task, and will stop
	 * the task if it's running.
	 * @see UpdateManager::startTask
	 * @param size Stack size in bytes.
	 */
	static void setStackSize(size_t size);

	static void addListener(UpdateListener* listener);
	static void removeListener(UpdateListener* listener);

	static void taskFunc(Task* task);

	static void update();

private:
	static Task task;
	static Vector<UpdateListener*> listeners;
	static uint lastMillis;
};


#endif //CIRCUITOS_UPDATEMANAGER_H
