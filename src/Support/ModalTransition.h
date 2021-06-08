#ifndef CIRCUITOS_MODALTRANSITION_H
#define CIRCUITOS_MODALTRANSITION_H

#include "../Loop/LoopListener.h"
#include "../UI/ElementContainer.h"
#include "../UI/LinearLayout.h"
#include "../UI/ScrollLayout.h"
#include "../UI/Image.h"
#include "Context.h"
#include "Modal.h"

class ModalTransition : public LoopListener {
public:
	ModalTransition(Display& display, Context* context, Modal* modal, bool reverse = false);

	void loop(uint micros) override;

	virtual ~ModalTransition();

	static bool isRunning();

	void setDoneCallback(void (* doneCallback)(Context*, Modal*));

private:
	bool reverse = false;

	Display* display;
	Context* context;
	Modal* modal;

	uint time = 0;
	uint lastScroll = 0;

	int modalX, modalY, contextX, contextY;

	void copySprite(Sprite* sprite, Sprite* targetSprite, int x = 0, int y = 0);

	static bool transitionRunning;

	void (*doneCallback)(Context* oldCtx, Modal* newCtx) = nullptr;
};


#endif //CIRCUITOS_MODALTRANSITION_H
