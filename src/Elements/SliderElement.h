#ifndef CIRCUITOS_SLIDERELEMENT_H
#define CIRCUITOS_SLIDERELEMENT_H

#include "../UI/SpriteElement.h"
#include "../UI/Layout.h"
#include "../UI/Image.h"
#include "../Loop/LoopListener.h"

class SliderElement : public Layout, public LoopListener {
public:
	SliderElement(ElementContainer* parent, uint width, uint height);
	~SliderElement();

	void update(uint millis) override;

	void start();
	void stop();

	Sprite* getImageSprite();

	void setStartListener(void (* listener)());
	void setStopListener(void (* listener)());
	void setShortListener(void (* listener)());
	void setLongListener(void (* listener)());
	void setCompleteListener(void (* listener)());

	void setSpeed(uint speed);

private:
	Image* image;

	uint started = false;
	uint progress = 0;
	uint speed = 5;

	void (*startListener)() = nullptr;
	void (*stopListener)() = nullptr;
	void (*shortListener)() = nullptr;
	void (*longListener)() = nullptr;
	void (*completeListener)() = nullptr;

	void reposChildren() override;

};


#endif //CIRCUITOS_SLIDERELEMENT_H
