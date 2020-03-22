#include "UpdateListener.h"
#include "UpdateManager.h"

UpdateListener::UpdateListener(){
	// UpdateManager::addListener(this);
}

UpdateListener::~UpdateListener(){
	UpdateManager::removeListener(this);
}
