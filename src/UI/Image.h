#ifndef CIRCUITOS_IMAGE_H
#define CIRCUITOS_IMAGE_H


#include "ElementContainer.h"

class Image : public Element {
public:
	Image(ElementContainer* parent, uint width, uint height);

	void draw() override;

	char* data;

	uint getWidth() override;

	uint getHeight() override;

	Sprite* getSprite() override;

private:
	uint width;
	uint height;

	Sprite sprite;
};


#endif //CIRCUITOS_IMAGE_H
