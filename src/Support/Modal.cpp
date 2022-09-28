#include "Modal.h"
#include "ModalTransition.h"

Modal* Modal::currentModal = nullptr;

Modal::Modal(Context& context, uint width, uint height) : Context(*context.getScreen().getDisplay()){
	screen.getSprite()->resize(width, height);

	posX = (context.getScreen().getDisplay()->getWidth() - width) / 2;
	posY = (context.getScreen().getDisplay()->getHeight() - height) / 2;

	setPos(posX, posY);
}

void Modal::pack(){
	currentModal = nullptr;
	if(packed) return;

	for(SpriteElement* element : sprites){
		element->pack();
	}

	packed = true;
	deinit();
}

void Modal::unpack(){
	currentModal = this;
	if(!packed) return;

	for(SpriteElement* element : sprites){
		element->unpack();
	}

	packed = false;
	init();
}

ContextTransition* Modal::push(Context* parent){
	this->parent = parent;
	return static_cast<ContextTransition*>((void*)new ModalTransition(*screen.getDisplay(), parent, this));
}

ContextTransition* Modal::pop(){
	if(parent == nullptr) return nullptr;
	auto transition = new ModalTransition(*screen.getDisplay(), parent, this, true);
	parent = nullptr;
	return static_cast<ContextTransition*>((void*)transition);
}

ContextTransition* Modal::pop(void* data){
	if(parent == nullptr) return nullptr;
	parent->returned(data);
	return pop();
}

int Modal::getPosX() const{
	return posX;
}

int Modal::getPosY() const{
	return posY;
}

void Modal::setPos(int posX, int posY){
	Modal::posX = posX;
	Modal::posY = posY;

	getScreen().setPos(posX, posY);
}

Modal *Modal::getCurrentModal(){
	return currentModal;
}
