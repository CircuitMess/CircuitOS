#ifndef CIRCUITOS_CACHELAYOUT_H
#define CIRCUITOS_CACHELAYOUT_H


#include "../Display/Sprite.h"
#include "Layout.h"
#include "SpriteElement.h"

class CacheLayout : public Layout, public SpriteElement {
public:
	CacheLayout(ElementContainer* parent);

	Sprite* getSprite() override;

	uint getWidth() override;
	uint getHeight() override;

	void draw() override;
	void reflow() override;
	void refresh();
};


#endif //CIRCUITOS_CACHELAYOUT_H
