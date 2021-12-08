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
	virtual ~Element();

	void setBorder(uint width, Color color);
	void setBorderColor(Color borderColor);
	void setBorderWidth(uint borderWidth);

	Color background = TFT_BLACK;
	Color borderColor;
	uint borderWidth = 0;

	Color chromaKey = TFT_TRANSPARENT;
	bool chroma = true;

	virtual uint getWidth() = 0;
	virtual uint getHeight() = 0;

	virtual void repos();
	virtual void draw();
	ElementContainer* getParent();
	void setParent(ElementContainer* parent);

	virtual int getTotalX() const;
	virtual int getTotalY() const;
	virtual int getX() const;
	virtual int getY() const;
	virtual void setX(int x);
	virtual void setY(int y);
	virtual void setPos(int x, int y);

	virtual Sprite* getSprite();

	virtual void clear();

private:
	ElementContainer* parent = nullptr;

	int x = 0;
	int y = 0;

};


#endif //CIRCUITOS_ELEMENT_H
