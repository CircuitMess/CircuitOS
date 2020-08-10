#ifndef CIRCUITOS_TEXTELEMENT_H
#define CIRCUITOS_TEXTELEMENT_H


#include "ElementContainer.h"
#include "../Display/Sprite.h"
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

	enum TextAlignment { LEFT, CENTER, RIGHT };
	void setAlignment(TextAlignment alignment);

private:
	uint width;
	uint height;

	uint textFont = 0;
	uint textSize = 1;
	Color textColor = TFT_DARKGREY;
	TextAlignment textAlignment = LEFT;

	std::string text = "";

};


#endif //CIRCUITOS_TEXTELEMENT_H
