#ifndef CIRCUITOS_MODAL_H
#define CIRCUITOS_MODAL_H


#include "Context.h"

class Modal : public Context {
public:
	Modal(Context& context, uint width, uint height);

	void push(Context* parent) override;
	void pop() override;
	void pop(void* data) override;

	int getPosX() const;
	int getPosY() const;

	void setPos(int posX,int posY);

private:
	int posX = 0;
	int posY = 0;

};


#endif //CIRCUITOS_MODAL_H
