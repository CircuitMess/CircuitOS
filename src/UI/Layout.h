#ifndef CIRCUITOS_LAYOUT_H
#define CIRCUITOS_LAYOUT_H


#include "ElementContainer.h"
#include "Element.h"

enum WHType { FIXED, CHILDREN, PARENT };

class Layout : public ElementContainer {
public:
	using ElementContainer::ElementContainer;

	virtual void reflow();
	virtual void repos() override;

	void draw() override;

	Layout& setPadding(uint padding);
	Layout& setGutter(uint gutter);

	uint getGutter() const;
	uint getPadding() const;

	void setWHType(WHType wType, WHType hType);
	void setWType(WHType wType);
	void setHType(WHType hType);
	WHType getWType() const;
	WHType getHType() const;

	void setWidth(uint width);
	void setHeight(uint height);
	uint getAvailableWidth() override;
	uint getAvailableHeight() override;
	uint getWidth() override;
	uint getHeight() override;

	void setStrictPos(bool strictPos);

protected:
	uint gutter = 0;
	uint padding = 0;

	WHType wType = FIXED;
	WHType hType = FIXED;

	bool strictPos = false;

private:
	uint width = 0;
	uint height = 0;

	virtual void reposChildren();
};


#endif //CIRCUITOS_LAYOUT_H
