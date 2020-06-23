#ifndef CIRCUITOS_CONTEXTTRANSITION_H
#define CIRCUITOS_CONTEXTTRANSITION_H

#include "../Update/UpdateListener.h"
#include "../Display/Display.h"

class Context;

class ContextTransition : public UpdateListener {
public:
	ContextTransition(Display& display, Context* contextA, Context* contextB);
	ContextTransition(Display& display, Context* contextA, Context* contextB, bool reverse);

	void update(uint micros) override;

	virtual ~ContextTransition();

private:
	bool reverse = false;

	Display* display;
	Context* contextA;

	Context* contextB;
	uint time = 0;

	uint lastScroll = 0;

	void copySprite(Sprite* sprite, Sprite* targetSprite, int pos);

};


#endif //CIRCUITOS_CONTEXTTRANSITION_H
