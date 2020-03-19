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

	uint getWidth() const override;

	uint getHeight() const override;

private:

	LayoutDirection direction;

	void draw() override;

	void reflowHorizontal();
	void reflowVertical();
};


#endif //CIRCUITOS_LINEARLAYOUT_H
