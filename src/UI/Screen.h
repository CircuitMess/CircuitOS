#ifndef CIRCUITOS_SCREEN_H
#define CIRCUITOS_SCREEN_H


#include "ElementContainer.h"
#include "Element.h"
#include "SpriteElement.h"
#include "../Setup.hpp"

class Screen : public ElementContainer, public SpriteElement {
public:
	explicit Screen(Display& display);
	Screen(Display& display, uint width, uint height);

	void pack() override;
	void unpack() override;

	Sprite* getSprite() override;

	void draw() override;

	Screen& addChild(Element* element) override;

	uint getAvailableWidth() override;
	uint getAvailableHeight() override;
	uint getWidth() override;
	uint getHeight() override;

	Display* getDisplay() const;

#ifndef CIRCUITOS_LOWRAM
	int getX() const override;
	int getY() const override;
#endif

	int getTotalX() const override;
	int getTotalY() const override;

	void setPos(int x, int y) override;

	void commit();

private:
	Display* display;

	uint width;
	uint height;

	/** Hiding */
#ifndef CIRCUITOS_LOWRAM
	using Element::setX;
	using Element::setY;
#endif
};


#endif //CIRCUITOS_SCREEN_H
