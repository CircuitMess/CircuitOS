#ifndef CIRCUITOS_ELEMENTCONTAINER_H
#define CIRCUITOS_ELEMENTCONTAINER_H


#include "../Util/Vector.h"
#include "Element.h"

class ElementContainer : public Element {
public:
	using Element::Element;

	virtual ElementContainer& addChild(Element* element);

	virtual uint getAvailableWidth() = 0;
	virtual uint getAvailableHeight() = 0;

	Element* getChild(int i) const;

	void draw() override;

protected:
	Vector<Element*> children;
};


#endif //CIRCUITOS_ELEMENTCONTAINER_H
