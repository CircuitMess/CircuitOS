#ifndef CIRCUITOS_CONTEXT_H
#define CIRCUITOS_CONTEXT_H


#include "../UI/Screen.h"
#include "../Input/Input.h"



class Context {
public:
	Context(Display& display);

	virtual void start() = 0;
	virtual void end() = 0;
	virtual void depress();
	virtual void compress();

	virtual void draw() = 0;

	void pop();
	void push(Context* parent);

	Screen& getScreen();

protected:
	Screen screen;
	Context* parent = nullptr;

	bool depressed = false;

};


#endif //CIRCUITOS_CONTEXT_H
