#include "ModalTransition.h"
#include "../Loop/LoopManager.h"

ModalTransition::ModalTransition(Display& display, Context* context, Modal* modal, bool reverse)
		: reverse(reverse), display(&display), context(context), modal(modal), tempSprite(display, display.getWidth(), display.getHeight()){

	modalX = modal->getScreen().getX();
	modalY = modal->getScreen().getY();

	if(reverse){
		modal->stop();
		modal->pack();

		context->unpack();
		context->getScreen().draw();

		modal->getScreen().getSprite()->setPos(modalX, modalY);
	}else{
		context->stop();
		context->pack();

		modal->unpack();
		modal->getScreen().draw();

		modal->getScreen().getSprite()->setPos(modalX, display.getHeight());
	}
	copySprite(display.getBaseSprite(), &tempSprite, 0, 0);
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

	int scroll = time / (100.5 * 1000.0);
	if(lastScroll < scroll){
		copySprite(context->getScreen().getSprite(), display->getBaseSprite());

		if(reverse){
			copySprite(&tempSprite, display->getBaseSprite(), 0, 0);
			copySprite(modal->getScreen().getSprite(), display->getBaseSprite(), modalX, modalY + scroll);
		}else{
			copySprite(&tempSprite, display->getBaseSprite(), 0, 0);
			copySprite(modal->getScreen().getSprite(), display->getBaseSprite(), modalX, max(modalY, (int) display->getHeight() - scroll));

		}

		lastScroll = scroll;
	}

	if(scroll >= (display->getHeight() - modalY)){
		modal->getScreen().setPos(modalX, modalY);

		if(reverse){
			context->getScreen().commit();
			context->start();
		}else{
			modal->getScreen().commit();
			modal->start();
		}

		delete this;
	}else{
		display->commit();
	}
}