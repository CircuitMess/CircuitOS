#ifndef CIRCUITOS_CUSTOMELEMENT_H
#define CIRCUITOS_CUSTOMELEMENT_H

#include <Arduino.h>
#include "ElementContainer.h"

class CustomElement : public Element {
public:
	CustomElement(ElementContainer* parent, uint width, uint height);

	uint getWidth() override;
	uint getHeight() override;

	void setWidth(uint width);
	void setHeight(uint height);

private:
	uint width = 0;
	uint height = 0;

};


#endif //CIRCUITOS_CUSTOMELEMENT_H
