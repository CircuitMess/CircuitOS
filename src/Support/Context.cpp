#include "Context.h"

bool Context::deleteOnPop = false;
Context* Context::currentContext = nullptr;

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
	currentContext = nullptr;
	if(packed) return;

	for(SpriteElement* element : sprites){
		element->pack();
	}

	packed = true;
	deinit();
}

void Context::unpack(){
	currentContext = this;
	if(!packed) return;

	for(SpriteElement* element : sprites){
		element->unpack();
	}

	packed = false;
	init();
}

ContextTransition* Context::pop(){
	if(parent == nullptr) return nullptr;
	ContextTransition* transition = new ContextTransition(*screen.getDisplay(), this, parent, true);
	if(deleteOnPop){
		transition->setDoneCallback([](Context* oldCtx, Context* newCtx){
			delete oldCtx;
		});
	}
	parent = nullptr;
	return transition;
}

ContextTransition* Context::pop(void* data){
	if(parent == nullptr) return nullptr;
	parent->returned(data);
	pop();
}

ContextTransition* Context::push(Context* parent){
	this->parent = parent;
	return new ContextTransition(*screen.getDisplay(), parent, this);

}

void Context::returned(void* data){

}

void Context::setDeleteOnPop(bool deleteOnPop){
	Context::deleteOnPop = deleteOnPop;
}

void Context::setParent(Context* parent){
	Context::parent = parent;
}

void Context::init(){}

void Context::deinit(){}

Context *Context::getCurrentContext(){
	return currentContext;
}
