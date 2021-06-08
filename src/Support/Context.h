#ifndef CIRCUITOS_CONTEXT_H
#define CIRCUITOS_CONTEXT_H

#include "../UI/Screen.h"
#include "ContextTransition.h"

class Context {
public:
	explicit Context(Display& display);
	virtual ~Context();

	virtual void draw() = 0;

	virtual void start() = 0;
	virtual void stop() = 0;

	virtual void addSprite(SpriteElement* sprite);
	virtual void pack();
	virtual void unpack();

	virtual ContextTransition* pop();
	virtual ContextTransition* pop(void* data);
	virtual ContextTransition* push(Context* parent);
	virtual void returned(void* data);

	Screen& getScreen();

	static void setDeleteOnPop(bool deleteOnPop);

	void setParent(Context* parent);

	static Context* getCurrentContext();

protected:
	Screen screen;
	Context* parent = nullptr;

	bool packed = false;

	Vector<SpriteElement*> sprites;

	static bool deleteOnPop;

	virtual void init();
	virtual void deinit();

private:
	static Context* currentContext;
};


#endif //CIRCUITOS_CONTEXT_H
