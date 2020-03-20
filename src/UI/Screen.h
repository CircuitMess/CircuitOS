#ifndef CIRCUITOS_SCREEN_H
#define CIRCUITOS_SCREEN_H


#include "ElementContainer.h"
#include "Element.h"

class Screen : public ElementContainer {
public:
	Screen(Display& display);

	void draw() override;
	void pushReverse() override;

	Screen& addChild(Element* element) override;

	uint getAvailableWidth() const override;

	uint getAvailableHeight() const override;

	uint getWidth() const override;

	uint getHeight() const override;

private:
	Display* display;

};


#endif //CIRCUITOS_SCREEN_H
