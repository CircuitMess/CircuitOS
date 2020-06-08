#ifndef CIRCUITOS_SPRITEELEMENT_H
#define CIRCUITOS_SPRITEELEMENT_H


#include "ElementContainer.h"

class SpriteElement {
public:
	SpriteElement(Sprite* parentSprite, uint width, uint height);
	virtual ~SpriteElement();

	virtual void pack();
	virtual void unpack();

	virtual uint getWidth() = 0;
	virtual uint getHeight() = 0;

	virtual Sprite* getSprite();

protected:
	Sprite sprite;
};


#endif //CIRCUITOS_SPRITEELEMENT_H
