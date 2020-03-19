#ifndef CIRCUITOS_ELEMENT_H
#define CIRCUITOS_ELEMENT_H


#include "../Display/Color.h"
#include "../Display/Sprite.h"
#include "ElementContainer.h"

class ElementContainer;

class Element {
public:
	Element(Sprite* parent);
	Element(ElementContainer* parent);

	void resize(uint width, uint height);

	Color background;
	Color borderColor;
	uint borderWidth;

	Color chromaKey = TFT_TRANSPARENT;
	bool chroma = true;

	Sprite* sprite;

	virtual uint getWidth() const = 0;
	virtual uint getHeight() const = 0;

	virtual void draw() = 0;
	ElementContainer* getParent();

private:
	ElementContainer* parent = nullptr;

};


#endif //CIRCUITOS_ELEMENT_H
