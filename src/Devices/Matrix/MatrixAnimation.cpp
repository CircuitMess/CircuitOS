#include "MatrixAnimation.h"
#include "Matrix.h"
#include "../../Loop/LoopManager.h"

MatrixAnimation::MatrixAnimation(){ }

MatrixAnimation::MatrixAnimation(Matrix* matrix, fs::File file) : matrix(matrix), gif(file){
	if(!gif) return;
	gif.nextFrame();
}

MatrixAnimation::~MatrixAnimation(){
	stop();
}

void MatrixAnimation::loop(uint time){
	if(!started){
		LoopManager::removeListener(this);
		return;
	}

	if(!gif){
		stop();
		return;
	}

	if(millis() - frameTime >= gif.frameDuration()){
		if(!gif.nextFrame()){
			stop();
			reset();
			return;
		}

		pushFrame();
		frameTime = millis();
	}
}

void MatrixAnimation::start(){
	if(!gif) return;

	if(started) return;
	started = true;

	frameTime = millis() - frameRemaining;

	pushFrame();

	LoopManager::addListener(this);
}

void MatrixAnimation::stop(){
	if(!started) return;
	started = false;

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

void MatrixAnimation::reset(){
	if(!gif) return;

	frameTime = frameRemaining = 0;
	gif.reset();
	gif.nextFrame();
}

void MatrixAnimation::pushFrame(){
	if(!gif) return;

	matrix->drawBitmap(0, 0, gif.getFrame());
	matrix->push();
}

GIF& MatrixAnimation::getGIF(){
	return gif;
}

MatrixAnimation::operator bool(){
	return gif;
}
