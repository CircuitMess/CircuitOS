#ifndef CIRCUITOS_UPDATEMANAGER_H
#define CIRCUITOS_UPDATEMANAGER_H


#include "../Util/Vector.h"
#include "UpdateListener.h"
#include "../Util/Task.h"

class UpdateManager {
public:
	static void startTask();

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
