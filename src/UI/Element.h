#ifndef CIRCUITOS_ELEMENT_H
#define CIRCUITOS_ELEMENT_H


#include "../Display/Color.h"
#include "../Display/Sprite.h"
#include "ElementContainer.h"

class ElementContainer;

class Element {
public:
	Element(Sprite* parent, uint width, uint height);
	Element(ElementContainer* parent, uint width, uint height);

	void resize(uint width, uint height);

	Color background;
	Color borderColor;
	uint borderWidth;

	Color chromaKey;
	bool chroma;

	uint width, height;

	Sprite* sprite;

	virtual void draw() = 0;
	ElementContainer* getParent();

private:
	ElementContainer* parent = nullptr;

};


#endif //CIRCUITOS_ELEMENT_H
