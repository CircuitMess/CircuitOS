#ifndef CIRCUITOS_ELEMENTCONTAINER_H
#define CIRCUITOS_ELEMENTCONTAINER_H


#include "../Util/Vector.h"
#include "Element.h"

class ElementContainer : public Element {
public:
	using Element::Element;

	virtual ElementContainer& addChild(Element* element);

	virtual uint getAvailableWidth() const = 0;
	virtual uint getAvailableHeight() const = 0;

	Element* getChild(int i) const;

protected:
	Vector<Element*> children;
};


#endif //CIRCUITOS_ELEMENTCONTAINER_H
