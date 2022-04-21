#include <Loop/LoopManager.h>
#include "MatrixAnimGIF.h"
#include "Matrix.h"

MatrixAnimGIF::MatrixAnimGIF(fs::File file, Matrix* matrix) : MatrixAnim(matrix), gif(std::move(file)){
	if(!gif) return;
	gif.nextFrame();

	setHeight(gif.getHeight());
	setWidth(gif.getWidth());
}

MatrixAnimGIF::~MatrixAnimGIF(){
	stop();
}

void MatrixAnimGIF::loop(uint delta){
	if(!isStarted()){
		LoopManager::removeListener(this);
		return;
	}

	if(!gif){
		stop();
		return;
	}

	uint32_t time = millis();
	uint32_t elapsed = time - frameTime;
	if(elapsed >= gif.frameDuration()){
		frameTime = time - (elapsed - gif.frameDuration());

		if(!gif.nextFrame()){
			stop();
			reset();
			return;
		}

		pushFrame();
	}
}

void MatrixAnimGIF::pushFrame(){
	if(!gif) return;

	drawBitmap(0, 0, gif.getFrame());
	push();
}

void MatrixAnimGIF::onStart(){
	if(!gif){
		stop();
		return;
	}

	frameTime = millis() - frameRemaining;

	pushFrame();

	LoopManager::addListener(this);
}

void MatrixAnimGIF::onStop(){
	LoopManager::removeListener(this);

	if(!gif) return;

	uint32_t frameLasted = millis() - frameTime;
	if(frameLasted < gif.frameDuration()){
		frameRemaining = gif.frameDuration() - frameLasted;
	}else{
		frameRemaining = 0;
	}

	frameTime = 0;
}

void MatrixAnimGIF::reset(){
	if(!gif) return;

	frameTime = frameRemaining = 0;
	gif.reset();
	gif.nextFrame();
}

GIF& MatrixAnimGIF::getGIF(){
	return gif;
}
