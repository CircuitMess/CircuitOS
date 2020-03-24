#ifndef CIRCUITOS_LAYEREDLAYOUT_H
#define CIRCUITOS_LAYEREDLAYOUT_H


#include "Layout.h"

class LayeredLayout : public Layout {
public:
	using Layout::Layout;

	void reflow() override;

	void draw() override;
};


#endif //CIRCUITOS_LAYEREDLAYOUT_H
