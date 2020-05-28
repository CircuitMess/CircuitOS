#ifndef CIRCUITOS_UPDATELISTENER_H
#define CIRCUITOS_UPDATELISTENER_H

#include <Arduino.h>

class UpdateListener {
public:
	UpdateListener();
	virtual ~UpdateListener();

	virtual void update(uint micros) = 0;
};


#endif //CIRCUITOS_UPDATELISTENER_H
