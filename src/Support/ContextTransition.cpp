#include "ContextTransition.h"
#include "../Update/UpdateManager.h"

ContextTransition::ContextTransition(Display& display, Context* contextA, Context* contextB) :
		ContextTransition(display, contextA, contextB, false){

}

ContextTransition::ContextTransition(Display& display, Context* contextA, Context* contextB, bool reverse)
	: reverse(reverse), display(&display), contextA(contextA), contextB(contextB) {

	contextA->end();
	contextA->compress();

	contextB->depress();
	contextB->getScreen().getSprite()->setPos(0, display.getHeight());
	contextB->draw();

	UpdateManager::addListener(this);
}

void ContextTransition::copySprite(Sprite* sprite, Sprite* targetSprite, int pos){
	Sprite* oldParent = sprite->getParent();
	uint oldX = sprite->getX();
	uint oldY = sprite->getY();

	sprite->setParent(targetSprite);
	sprite->setPos(0, pos);

	sprite->push();

	sprite->setParent(oldParent);
	sprite->setPos(oldX, oldY);
}

void ContextTransition::update(uint millis){
	time += millis;

	uint scroll = time / 1.5;
	if(lastScroll < scroll){

		if(reverse){
			//copySprite(display->getBaseSprite(), display->getBaseSprite(), 1);
			copySprite(contextB->getScreen().getSprite(), display->getBaseSprite(), (int) scroll - (int) display->getHeight());
		}else{
			copySprite(display->getBaseSprite(), display->getBaseSprite(), -1);
			copySprite(contextB->getScreen().getSprite(), display->getBaseSprite(), display->getHeight() - scroll);
		}

		lastScroll = scroll;
	}

	if(scroll >= display->getHeight()){
		Serial.println("Ending context switch");
		contextB->getScreen().setPos(0, 0);
		contextB->getScreen().commit();
		contextB->start();
		delete this;
	}else{
		display->commit();
	}
}