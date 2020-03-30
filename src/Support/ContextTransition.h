#ifndef CIRCUITOS_CONTEXTTRANSITION_H
#define CIRCUITOS_CONTEXTTRANSITION_H

#include "../Update/UpdateListener.h"
#include "../UI/ElementContainer.h"
#include "../UI/LinearLayout.h"
#include "../UI/ScrollLayout.h"
#include "../UI/Image.h"
#include "Context.h"

class ContextTransition : public UpdateListener {
public:
	ContextTransition(Display& display, Context* contextA, Context* contextB);
	ContextTransition(Display& display, Context* contextA, Context* contextB, bool reverse);

	void update(uint millis) override;

	virtual ~ContextTransition();

private:

	Display* display;

	Context* contextA;
	Context* contextB;

	uint time = 0;
	uint lastScroll = 0;

	bool reverse = false;

	void copySprite(Sprite* sprite, Sprite* targetSprite, int pos);

};


#endif //CIRCUITOS_CONTEXTTRANSITION_H
