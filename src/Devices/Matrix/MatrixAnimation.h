#ifndef SPENCER_ANIMATION_H
#define SPENCER_ANIMATION_H

#include <Arduino.h>
#include <FS.h>
#include "../../Loop/LoopListener.h"
#include "../../Util/GIF.h"

class Matrix;

class MatrixAnimation : public LoopListener {
public:
	MatrixAnimation();
	MatrixAnimation(Matrix* matrix, fs::File file);
	~MatrixAnimation();

	GIF& getGIF();
	operator bool();

	void start();
	void stop();
	void reset();

	void loop(uint time);

private:
	Matrix* matrix;
	GIF gif;
	bool started = false;

	uint32_t frameTime = 0;
	uint32_t frameRemaining = 0;

	void pushFrame();

};



#endif