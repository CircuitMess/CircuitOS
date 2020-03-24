#ifndef CIRCUITOS_CACHELAYOUT_H
#define CIRCUITOS_CACHELAYOUT_H


#include "../Display/Sprite.h"
#include "Layout.h"

class CacheLayout : public Layout {
public:
	CacheLayout(ElementContainer* parent);

	Sprite* getSprite() override;

	void draw() override;

	void reflow() override;

	void refresh();

private:
	Sprite sprite;
};


#endif //CIRCUITOS_CACHELAYOUT_H
