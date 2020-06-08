#ifndef CIRCUITOS_TEXTELEMENT_H
#define CIRCUITOS_TEXTELEMENT_H


#include "ElementContainer.h"
#include <string>

class TextElement : public Element {
public:
	TextElement(ElementContainer* parent, uint width, uint height);

	TextElement& setFont(uint font);
	TextElement& setSize(uint fontSize);
	TextElement& setColor(Color fontColor);

	void draw() override;

	const std::string& getText() const;
	void setText(const std::string& text);

	uint getWidth() override;
	uint getHeight() override;

	void setWidth(uint width);

	void setHeight(uint height);

private:
	uint width;
	uint height;

	uint textFont = 0;
	uint textSize = 1;
	Color textColor = TFT_DARKGREY;

	std::string text = "";

};


#endif //CIRCUITOS_TEXTELEMENT_H
