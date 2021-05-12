#ifndef CIRCUITOS_CONTEXTTRANSITION_H
#define CIRCUITOS_CONTEXTTRANSITION_H

#include "../Loop/LoopListener.h"
#include "../Display/Display.h"

class Context;

class ContextTransition : public LoopListener {
public:
	ContextTransition(Display& display, Context* contextA, Context* contextB);
	ContextTransition(Display& display, Context* contextA, Context* contextB, bool reverse);

	void setDoneCallback(void (* doneCallback)(Context*, Context*));

	void loop(uint micros) override;

	virtual ~ContextTransition();

	bool isRunning();

private:
	bool reverse = false;

	Display* display;
	Context* contextA;

	Context* contextB;
	uint time = 0;

	uint lastScroll = 0;

	void copySprite(Sprite* sprite, Sprite* targetSprite, int pos);

	void (*doneCallback)(Context* oldCtx, Context* newCtx) = nullptr;

	static bool transitionRunning;
};


#endif //CIRCUITOS_CONTEXTTRANSITION_H
