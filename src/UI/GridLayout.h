#ifndef CIRCUITOS_GridLayout_H
#define CIRCUITOS_GridLayout_H

#include "Layout.h"

class GridLayout : public Layout {
public:
	GridLayout(ElementContainer* parent, uint cols);

	void reposChildren() override;
	void reflow() override;
	void draw() override;

private:

	uint cols;

};


#endif //CIRCUITOS_GridLayout_H
