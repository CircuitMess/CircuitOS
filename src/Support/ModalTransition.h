#ifndef CIRCUITOS_MODALTRANSITION_H
#define CIRCUITOS_MODALTRANSITION_H

#include "../Loop/LoopListener.h"
#include "../UI/ElementContainer.h"
#include "../UI/LinearLayout.h"
#include "../UI/ScrollLayout.h"
#include "../UI/Image.h"
class Modal;
class Context;

class ModalTransition : public LoopListener {
public:
	ModalTransition(Display& display, Context* context, Modal* modal, bool reverse = false);

	void loop(uint micros) override;

	virtual ~ModalTransition();

	static bool isRunning();

	void setDoneCallback(void (* doneCallback)(Context*, Modal*));

	static void setDeleteOnPop(bool deleteOnPop);

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

	static bool deleteOnPop;
};


#endif //CIRCUITOS_MODALTRANSITION_H
