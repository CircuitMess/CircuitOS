#include "ModalTransition.h"
#include "../Loop/LoopManager.h"

bool ModalTransition::transitionRunning = false;

ModalTransition::ModalTransition(Display& display, Context* context, Modal* modal, bool reverse)
		: reverse(reverse), display(&display), context(context), modal(modal){

	transitionRunning = true;
	modalX = modal->getScreen().getX();
	modalY = modal->getScreen().getY();
	contextX = context->getScreen().getX();
	contextY = context->getScreen().getY();


	if(reverse){
		modal->stop();

		context->unpack();
		context->draw();

		modal->getScreen().getSprite()->setPos(modalX, modalY);
	}else{
		context->stop();

		modal->unpack();
		modal->draw();

		modal->getScreen().getSprite()->setPos(modalX, display.getHeight());
	}
	LoopManager::addListener(this);
}

ModalTransition::~ModalTransition(){
	transitionRunning = false;
	LoopManager::removeListener(this);
}

void ModalTransition::copySprite(Sprite* sprite, Sprite* targetSprite, int x, int y){
	Sprite* oldParent = sprite->getParent();
	uint oldX = sprite->getX();
	uint oldY = sprite->getY();

	sprite->setParent(targetSprite);
	sprite->setPos(x, y);

	sprite->push();

	sprite->setParent(oldParent);
	sprite->setPos(oldX, oldY);
}

void ModalTransition::loop(uint micros){
	time += micros;

	int scroll = time / (100.5 * 1000.0);
	if(lastScroll < scroll){
		copySprite(context->getScreen().getSprite(), display->getBaseSprite(), contextX, contextY);

		if(reverse){
			copySprite(context->getScreen().getSprite(), display->getBaseSprite(), contextX, contextY);
			copySprite(modal->getScreen().getSprite(), display->getBaseSprite(), modalX, modalY + scroll);
		}else{
			copySprite(context->getScreen().getSprite(), display->getBaseSprite(), contextX, contextY);
			copySprite(modal->getScreen().getSprite(), display->getBaseSprite(), modalX, max(modalY, (int) display->getHeight() - scroll));

		}

		lastScroll = scroll;
	}

	if(scroll >= (display->getHeight() - modalY)){
		modal->getScreen().setPos(modalX, modalY);

		if(reverse){
			modal->pack();
			delete modal;
			context->unpack();
			context->getScreen().commit();
			context->start();
		}else{
			context->pack();
			modal->unpack();
			modal->getScreen().commit();
			modal->start();
		}

		delete this;
	}else{
		display->commit();
	}
}

bool ModalTransition::isRunning(){
	return transitionRunning;
}