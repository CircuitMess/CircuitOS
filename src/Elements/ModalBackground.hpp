#ifndef CIRCUITOS_MODALBG_H
#define CIRCUITOS_MODALBG_H

#include "../UI/CustomElement.h"

class ModalBackground : public CustomElement {
public:
	ModalBackground(ElementContainer *parent, uint width, uint height, Color bgColor, Color topColor, Color botColor) :
			CustomElement(parent, width, height), bgColor(bgColor), borderTopColor(topColor), borderBotColor(botColor){
		getSprite()->setChroma(TFT_TRANSPARENT);
	}

	ModalBackground(ElementContainer *parent, uint width, uint height, Color _bgColor) :
			ModalBackground(parent, width, height, _bgColor, (_bgColor & 0x7BEF) << 1,(_bgColor & 0xF7DE) >> 1){
	}

	void draw() override{
		Sprite *canvas = getSprite();

		canvas->clear(TFT_TRANSPARENT);
		canvas->fillRect(getTotalX(), getTotalY() + 2, getWidth(), getHeight() - 4, bgColor);
		canvas->drawFastHLine(getTotalX() + 1, getTotalY(), getWidth() - 2, borderTopColor);
		canvas->drawFastHLine(getTotalX(), getTotalY() + 1, getWidth(), borderTopColor);
		canvas->drawFastHLine(getTotalX(), getTotalY() + getHeight() - 2, getWidth(), borderBotColor);
		canvas->drawFastHLine(getTotalX() + 1, getTotalY() + getHeight() - 1, getWidth() - 2, borderBotColor);

		if(border){
			canvas->drawFastVLine(getTotalX() + 0, getTotalY() + 2, getHeight() - 4, borderTopColor);
			canvas->drawFastVLine(getTotalX() + 1, getTotalY() + 2, getHeight() - 4, borderTopColor);
			canvas->drawFastVLine(getTotalX() + getWidth() - 2, getTotalY() + 2, getHeight() - 4, borderTopColor);
			canvas->drawFastVLine(getTotalX() + getWidth() - 1, getTotalY() + 2, getHeight() - 4, borderTopColor);
		}
	}

	bool border = false;

	const Color bgColor;
	Color borderTopColor;
	Color borderBotColor;

};

#endif //CIRCUITOS_MODALBG_H
