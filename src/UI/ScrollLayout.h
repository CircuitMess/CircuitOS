#ifndef CIRCUITOS_SCROLLLAYOUT_H
#define CIRCUITOS_SCROLLLAYOUT_H


#include "Layout.h"

class ScrollLayout : public Layout {
public:
	ScrollLayout(ElementContainer* parent);
	void reflow() override;

	ElementContainer& addChild(Element* element) override;

	void setScroll(uint scrollX, uint scrollY);

	uint getMaxScrollX() const;
	uint getMaxScrollY() const;

private:
	void draw() override;

	uint scrollX = 0;
	uint scrollY = 0;
};


#endif //CIRCUITOS_SCROLLLAYOUT_H
