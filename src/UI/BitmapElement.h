#ifndef CIRCUITOS_BITMAPELEMENT_H
#define CIRCUITOS_BITMAPELEMENT_H


#include "ElementContainer.h"

class BitmapElement : public Element {
public:
	BitmapElement(ElementContainer* parent, const uint16_t* bitmap, uint width, uint height);

	void draw() override;

	uint getWidth() override;
	uint getHeight() override;

private:
	const uint16_t* bitmap;

	uint width;
	uint height;

};


#endif //CIRCUITOS_BITMAPELEMENT_H
