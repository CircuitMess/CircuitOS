#include <Loop/LoopManager.h>
#include "MatrixAnimGIF.h"
#include "Matrix.h"
#include <FSImpl.h>

MatrixAnimGIF::MatrixAnimGIF(fs::File file, Matrix* matrix) : MatrixAnim(matrix), gif(std::move(file)){
	if(!gif) return;
	gif.nextFrame();

	setHeight(gif.getHeight());
	setWidth(gif.getWidth());

	auto temp = gif.getLoopMode();
	gif.setLoopMode(GIF::SINGLE);
	while(gif.nextFrame()){
		totalDuration+=gif.frameDuration();
	}
	gif.reset();
	gif.nextFrame();
	gif.setLoopMode(temp);
}

MatrixAnimGIF::MatrixAnimGIF(fs::FileImpl* file, Matrix* matrix) : MatrixAnimGIF(fs::File(fs::FileImplPtr(file)), matrix){

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

		push();
	}
}

void MatrixAnimGIF::push(){
	if(!gif) return;

	drawBitmap(0, 0, gif.getFrame());
	pushMatrix();
}

void MatrixAnimGIF::onStart(){
	if(!gif){
		stop();
		return;
	}

	startTime = millis();
	frameTime = millis() - frameRemaining;

	push();

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

	gif.reset();
	gif.nextFrame();
	frameTime = millis();
	frameRemaining = 0;
	push();

	startTime = millis();
}

GIF& MatrixAnimGIF::getGIF(){
	return gif;
}

float MatrixAnimGIF::getCompletionPercentage(){
	float elapsed = millis() - startTime;
	return (elapsed / totalDuration);
}

uint32_t MatrixAnimGIF::getLoopDuration() const{
	return totalDuration;
}
