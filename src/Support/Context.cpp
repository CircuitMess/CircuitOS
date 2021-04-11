#include "Context.h"
#include "ContextTransition.h"

bool Context::deleteOnPop = false;

Context::Context(Display& display) : screen(display){
	addSprite(&screen);
}

Context::~Context(){

}

Screen& Context::getScreen(){
	return screen;
}

void Context::addSprite(SpriteElement* sprite){
	sprites.push_back(sprite);
}

void Context::pack(){
	if(packed) return;

	for(SpriteElement* element : sprites){
		element->pack();
	}

	packed = true;
}

void Context::unpack(){
	if(!packed) return;

	for(SpriteElement* element : sprites){
		element->unpack();
	}

	packed = false;
}

void Context::pop(){
	if(parent == nullptr) return;
	ContextTransition* transition = new ContextTransition(*screen.getDisplay(), this, parent, true);
	if(deleteOnPop){
		transition->setDoneCallback([](Context* oldCtx, Context* newCtx){
			delete oldCtx;
		});
	}
	parent = nullptr;
}

void Context::pop(void* data){
	if(parent == nullptr) return;
	parent->returned(data);
	pop();
}

void Context::push(Context* parent){
	this->parent = parent;
	new ContextTransition(*screen.getDisplay(), parent, this);
}

void Context::returned(void* data){

}

void Context::setDeleteOnPop(bool deleteOnPop){
	Context::deleteOnPop = deleteOnPop;
}
