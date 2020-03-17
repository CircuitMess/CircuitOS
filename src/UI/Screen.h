#ifndef CIRCUITOS_SCREEN_H
#define CIRCUITOS_SCREEN_H


#include "ElementContainer.h"
#include "Element.h"

class Screen : public ElementContainer {
public:
	Screen(Display& display);

	void draw() override;

	Screen& addChild(Element& element);

	uint getAvailableWidth() override;

	uint getAvailableHeight() override;

private:
	Display* display;

};


#endif //CIRCUITOS_SCREEN_H
