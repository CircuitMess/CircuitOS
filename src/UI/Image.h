#ifndef CIRCUITOS_IMAGE_H
#define CIRCUITOS_IMAGE_H


#include "ElementContainer.h"

class Image : public Element {
public:
	Image(ElementContainer* parent, uint width, uint height);

	void draw() override;

	char* data;

	uint getWidth() const override;

	uint getHeight() const override;

private:
	uint width;
	uint height;

};


#endif //CIRCUITOS_IMAGE_H
