#include "Context.h"
#include "ContextTransition.h"

Context::Context(Display& display) : screen(display){

}

Screen& Context::getScreen(){
	return screen;
}

void Context::depress(){
	depressed = true;
}

void Context::compress(){
	depressed = false;
}

void Context::pop(){
	new ContextTransition(*screen.getDisplay(), this, parent, true);
	parent = nullptr;
}

void Context::push(Context* parent){
	this->parent = parent;
	new ContextTransition(*screen.getDisplay(), parent, this);
}
