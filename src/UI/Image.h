#ifndef CIRCUITOS_IMAGE_H
#define CIRCUITOS_IMAGE_H


#include "ElementContainer.h"

class Image : public Element {
public:
	using Element::Element;

	void draw() override;

	char* data;

private:

};


#endif //CIRCUITOS_IMAGE_H
