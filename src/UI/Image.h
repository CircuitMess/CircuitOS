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

	void setWidth(uint width);
	void setHeight(uint height);
	void setSize(uint width, uint height);

private:
	uint width;
	uint height;

};


#endif //CIRCUITOS_IMAGE_H
