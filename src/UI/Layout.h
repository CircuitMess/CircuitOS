#ifndef CIRCUITOS_LAYOUT_H
#define CIRCUITOS_LAYOUT_H


#include "ElementContainer.h"
#include "Element.h"

enum WHType { FIXED, CHILDREN, PARENT };

class Layout : public ElementContainer {
public:
	using ElementContainer::ElementContainer;

	virtual void reflow() = 0;

	Layout& setPadding(uint padding);
	Layout& setGutter(uint gutter);

	void setWidth(uint width);
	void setHeight(uint height);

protected:
	uint gutter = 0;
	uint padding = 0;
	uint width = 0;
	uint height = 0;

private:
	WHType hType;
	WHType wType;

};


#endif //CIRCUITOS_LAYOUT_H
