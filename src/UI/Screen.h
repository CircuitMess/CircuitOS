#ifndef CIRCUITOS_SCREEN_H
#define CIRCUITOS_SCREEN_H


#include "ElementContainer.h"
#include "Element.h"

class Screen : public ElementContainer {
public:
	Screen(Display& display);

	void draw() override;

	Screen& addChild(Element* element) override;

	uint getAvailableWidth() override;

	uint getAvailableHeight() override;

	uint getWidth() override;

	uint getHeight() override;

	Display* getDisplay() const;

	Sprite* getSprite() override;

	uint getX() const override;
	uint getY() const override;
	uint getTotalX() const override;
	uint getTotalY() const override;

	void setPos(uint x, uint y) override;

	void commit();

private:
	Display* display;
	Sprite sprite;

	/** Hiding */
	using Element::setX;
	using Element::setY;
};


#endif //CIRCUITOS_SCREEN_H
