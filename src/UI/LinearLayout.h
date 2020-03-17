#ifndef CIRCUITOS_LINEARLAYOUT_H
#define CIRCUITOS_LINEARLAYOUT_H

#include "Layout.h"

enum LayoutDirection { HORIZONTAL, VERTICAL };

class LinearLayout : public Layout {
public:
	LinearLayout(ElementContainer* parent, LayoutDirection direction);

	uint getAvailableWidth() override;

	uint getAvailableHeight() override;

	void reflow() override;
private:

	void draw() override;

	LayoutDirection direction;

};


#endif //CIRCUITOS_LINEARLAYOUT_H
