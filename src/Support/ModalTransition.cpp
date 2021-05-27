#include "ModalTransition.h"
#include "../Loop/LoopManager.h"

ModalTransition::ModalTransition(Display& display, Context* context, Modal* modal, bool reverse)
		: reverse(reverse), display(&display), context(context), modal(modal){

	modalX = modal->getScreen().getX();
	modalY = modal->getScreen().getY();

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

	int scroll = time / (1.5 * 1000.0);
	if(lastScroll < scroll){
		copySprite(context->getScreen().getSprite(), display->getBaseSprite());

		if(reverse){
			copySprite(context->getScreen().getSprite(), display->getBaseSprite(), 0, 0);
			copySprite(modal->getScreen().getSprite(), display->getBaseSprite(), modalX, modalY + scroll);
		}else{
			copySprite(context->getScreen().getSprite(), display->getBaseSprite(), 0, 0);
			copySprite(modal->getScreen().getSprite(), display->getBaseSprite(), modalX, max(modalY, (int) display->getHeight() - scroll));

		}

		lastScroll = scroll;
	}

	if(scroll >= (display->getHeight() - modalY)){
		modal->getScreen().setPos(modalX, modalY);

		if(reverse){
			modal->pack();
			delete modal;
			context->getScreen().commit();
			context->start();
		}else{
			context->pack();
			modal->getScreen().commit();
			modal->start();
		}

		delete this;
	}else{
		display->commit();
	}
}