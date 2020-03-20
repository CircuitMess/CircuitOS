#ifndef CIRCUITOS_GridLayout_H
#define CIRCUITOS_GridLayout_H

#include "Layout.h"

class GridLayout : public Layout {
public:
	GridLayout(ElementContainer* parent, uint cols);

	void reflow() override;

private:
	uint cols;

	void draw() override;

};


#endif //CIRCUITOS_GridLayout_H
