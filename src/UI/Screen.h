#ifndef CIRCUITOS_SCREEN_H
#define CIRCUITOS_SCREEN_H


#include "ElementContainer.h"
#include "Element.h"
#include "SpriteElement.h"

class Screen : public ElementContainer, public SpriteElement {
public:
	Screen(Display& display);

	Sprite* getSprite() override;

	void draw() override;

	Screen& addChild(Element* element) override;

	uint getAvailableWidth() override;

	uint getAvailableHeight() override;

	uint getWidth() override;

	uint getHeight() override;

	Display* getDisplay() const;

	uint getX() const override;
	uint getY() const override;
	uint getTotalX() const override;
	uint getTotalY() const override;

	void setPos(uint x, uint y) override;

	void commit();

private:
	Display* display;

	/** Hiding */
	using Element::setX;
	using Element::setY;
};


#endif //CIRCUITOS_SCREEN_H
