#ifndef CIRCUITOS_ELEMENT_H
#define CIRCUITOS_ELEMENT_H


#include "../Display/Color.h"
#include "../Display/Sprite.h"
#include "ElementContainer.h"

class ElementContainer;

class Element {
public:
	Element();
	Element(ElementContainer* parent);

	void setBorder(uint width, Color color);
	void setBorderColor(Color borderColor);
	void setBorderWidth(uint borderWidth);

	Color background;
	Color borderColor;
	uint borderWidth = 0;

	Color chromaKey = TFT_TRANSPARENT;
	bool chroma = true;

	virtual uint getWidth() = 0;
	virtual uint getHeight() = 0;

	virtual void draw();
	ElementContainer* getParent();

	virtual uint getTotalX() const;
	virtual uint getTotalY() const;
	virtual uint getX() const;
	virtual uint getY() const;
	virtual void setX(uint x);
	virtual void setY(uint y);
	virtual void setPos(uint x, uint y);

	virtual Sprite* getSprite();

	virtual void clear();

private:
	ElementContainer* parent = nullptr;

	uint x = 0;
	uint y = 0;

};


#endif //CIRCUITOS_ELEMENT_H
