#include <Arduino.h>
#include "src/CircuitOS.h"

Display display(160, 128);
Sprite sprite(display, 50, 50);
Sprite sprite2(display, 20, 20);
Sprite sprite3(display, 20, 20);
Sprite sprite4(&sprite, 10, 10);
unsigned i = 0;
unsigned j = 0;
unsigned k = 0;

void setup(){
	Serial.begin(115200);

	display.clear(TFT_GREEN);
	sprite.setPos(10, 10).clear(TFT_BLUE).push();
	sprite2.setPos(10, 10).clear(TFT_RED).push();
	sprite3.setPos(10, 10).clear(TFT_GOLD).push();
	sprite4.setPos(10, 10).clear(TFT_OLIVE).push();
	display.commit();
}

void loop(){
	// push child sprite to parent sprite

	sprite.setPos(10, 10 + i);
	sprite2.setPos(10 + j, 10);
	sprite3.setPos(10 + j, 10 + i);
	sprite4.setPos(10 + k, 10 + k);

	display.clear(TFT_GREEN);
	sprite.clear(TFT_BLUE);
	sprite4.push();
	sprite.push();
	sprite2.push();
	sprite3.push();

	display.commit();

	//delay(5);
	if(i++ >= 60) i = 0;
	if(j++ >= 120) j = 0;
	if(k++ >= 20) k = 0;
}

