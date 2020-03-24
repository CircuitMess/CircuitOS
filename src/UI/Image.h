#ifndef CIRCUITOS_IMAGE_H
#define CIRCUITOS_IMAGE_H


#include "ElementContainer.h"
#include "SpriteElement.h"

class Image : public Element, public SpriteElement {
public:
	Image(ElementContainer* parent, uint width, uint height);

	Sprite* getSprite() override;

	void draw() override;

	uint getWidth() override;

	uint getHeight() override;

private:
	uint width;
	uint height;

};


#endif //CIRCUITOS_IMAGE_H
