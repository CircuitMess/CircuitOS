#ifndef CIRCUITOS_SCREEN_H
#define CIRCUITOS_SCREEN_H


#include "ElementContainer.h"
#include "Element.h"
#include "SpriteElement.h"

class Screen : public ElementContainer, public SpriteElement {
public:
	explicit Screen(Display& display);
	Screen(Display& display, uint width, uint height);

	Sprite* getSprite() override;

	void draw() override;

	Screen& addChild(Element* element) override;

	uint getAvailableWidth() override;

	uint getAvailableHeight() override;

	uint getWidth() override;

	uint getHeight() override;

	Display* getDisplay() const;

	int getX() const override;
	int getY() const override;
	int getTotalX() const override;
	int getTotalY() const override;

	void setPos(int x, int y) override;

	void commit();

private:
	Display* display;

	/** Hiding */
	using Element::setX;
	using Element::setY;
};


#endif //CIRCUITOS_SCREEN_H
