#ifndef CIRCUITOS_CONTEXT_H
#define CIRCUITOS_CONTEXT_H

#include "../UI/Screen.h"

class Context {
public:
	explicit Context(Display& display);

	virtual void draw() = 0;

	virtual void start() = 0;
	virtual void stop() = 0;

	virtual void addSprite(SpriteElement* sprite);
	virtual void pack();
	virtual void unpack();

	virtual void pop();
	virtual void pop(void* data);
	virtual void push(Context* parent);
	virtual void returned(void* data);

	Screen& getScreen();

protected:
	Screen screen;
	Context* parent = nullptr;

	bool packed = false;

	Vector<SpriteElement*> sprites;

};


#endif //CIRCUITOS_CONTEXT_H
