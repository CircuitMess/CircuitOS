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

	void setWHType(WHType wType, WHType hType);
	void setWType(WHType wType);
	void setHType(WHType hType);
	WHType getWType() const;
	WHType getHType() const;

protected:
	uint gutter = 0;
	uint padding = 0;
	uint width = 0;
	uint height = 0;

	WHType wType = FIXED;
	WHType hType = FIXED;

};


#endif //CIRCUITOS_LAYOUT_H
