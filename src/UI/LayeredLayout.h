#ifndef CIRCUITOS_LAYEREDLAYOUT_H
#define CIRCUITOS_LAYEREDLAYOUT_H


#include "Layout.h"

class LayeredLayout : public Layout {
public:
	using Layout::Layout;

	void reflow() override;

	void draw() override;

	void pushReverse() override;
};


#endif //CIRCUITOS_LAYEREDLAYOUT_H
