#ifndef CIRCUITOS_WITHLISTENERS_H
#define CIRCUITOS_WITHLISTENERS_H

#include <unordered_set>
#include <functional>

template<typename T>
class WithListeners {
public:
	void addListener(T* listener) {
		listeners.insert(listener);
	}

	void removeListener(T* listener){
		auto it = listeners.find(listener);
		if(it == listeners.end()) return;

		listeners.erase(it);
	}

protected:
	/**
	 * Notify all listeners that something has changed.
	 *
	 * @param func Function to be called on all listeners
	 */
	void iterateListeners(std::function<void(T*)> func){
		auto listenersCopy(listeners);
		for(auto listener : listenersCopy){
			func(listener);
		}
	}

private:
	std::unordered_set<T*> listeners;
};
#endif //CIRCUITOS_WITHLISTENERS_H
