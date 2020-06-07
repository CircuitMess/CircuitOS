#include "Modal.h"
#include "ModalTransition.h"

Modal::Modal(Context& context, uint width, uint height) : Context(*context.getScreen().getDisplay()){
	screen.getSprite()->resize(width, height);

	posX = (context.getScreen().getDisplay()->getWidth() - width) / 2;
	posY = (context.getScreen().getDisplay()->getHeight() - height) / 2;

	setPos(posX, posY);
}

void Modal::push(Context* parent){
	this->parent = parent;
	new ModalTransition(*screen.getDisplay(), parent, this);
}

void Modal::pop(){
	new ModalTransition(*screen.getDisplay(), parent, this, true);
	parent = nullptr;
}

void Modal::pop(void* data){
	parent->returned(data);
	pop();
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
