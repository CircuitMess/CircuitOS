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

	virtual ~Element();

	void resize(uint width, uint height);
	void resizeSprite();

	void setBorder(uint width, Color color);
	void setBorderColor(Color borderColor);
	void setBorderWidth(uint borderWidth);

	Color background;
	Color borderColor;
	uint borderWidth = 0;

	Color chromaKey = TFT_TRANSPARENT;
	bool chroma = true;

	Sprite* sprite;

	virtual uint getWidth() const = 0;
	virtual uint getHeight() const = 0;

	virtual void draw();
	virtual void pushReverse();
	ElementContainer* getParent();

private:
	ElementContainer* parent = nullptr;

};


#endif //CIRCUITOS_ELEMENT_H
