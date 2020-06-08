#ifndef CIRCUITOS_SCROLLLAYOUT_H
#define CIRCUITOS_SCROLLLAYOUT_H


#include "Layout.h"

class ScrollLayout : public Layout {
public:
	ScrollLayout(ElementContainer* parent);
	ElementContainer& addChild(Element* element) override;

	void setScroll(uint scrollX, uint scrollY);

	uint getMaxScrollX();
	uint getMaxScrollY();

	uint getScrollX() const;
	uint getScrollY() const;

	/**
	 * Scroll a child of the containing element into view. Causes unexpected behaviour if the child of this element
	 * isn't an ElementContainer.
	 * @param child
	 * @param over How much to scroll past the element
	 */
	void scrollIntoView(uint child, int over = 0);

	void reposChildren() override;
	void draw() override;

private:

	uint scrollX = 0;
	uint scrollY = 0;
};


#endif //CIRCUITOS_SCROLLLAYOUT_H
