#include "Context.h"
#include "ContextTransition.h"

Context::Context(Display& display) : screen(display){

}

Screen& Context::getScreen(){
	return screen;
}

void Context::addSprite(SpriteElement* sprite){
	sprites.push_back(sprite);
}

void Context::pack(){
	for(SpriteElement* element : sprites){
		element->pack();
	}

	packed = true;
}

void Context::unpack(){
	for(SpriteElement* element : sprites){
		element->unpack();
	}

	packed = false;
}

void Context::pop(){
	new ContextTransition(*screen.getDisplay(), this, parent, true);
	parent = nullptr;
}

void Context::push(Context* parent){
	this->parent = parent;
	new ContextTransition(*screen.getDisplay(), parent, this);
}
