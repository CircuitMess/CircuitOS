#ifndef CIRCUITOS_MODAL_H
#define CIRCUITOS_MODAL_H


#include "Context.h"
#include "ModalTransition.h"

class Modal : public Context {
public:
	Modal(Context& context, uint width, uint height);

	void pack() override;
	void unpack() override;

	ContextTransition* push(Context* parent) override;
	ContextTransition* pop() override;
	ContextTransition* pop(void* data) override;

	int getPosX() const;
	int getPosY() const;

	void setPos(int posX,int posY);

	static Modal* getCurrentModal();



private:
	int posX = 0;
	int posY = 0;

	static Modal* currentModal;


};


#endif //CIRCUITOS_MODAL_H
