#ifndef CIRCUITOS_LINEARLAYOUT_H
#define CIRCUITOS_LINEARLAYOUT_H

#include "Layout.h"

enum LayoutDirection { HORIZONTAL, VERTICAL };

class LinearLayout : public Layout {
public:
	LinearLayout(ElementContainer* parent, LayoutDirection direction);

	void reflow() override;
	void reposChildren() override;

private:

	LayoutDirection direction;

	void reflowHorizontal();
	void reflowVertical();
};


#endif //CIRCUITOS_LINEARLAYOUT_H
