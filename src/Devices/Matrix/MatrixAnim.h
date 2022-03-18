#ifndef SPENCER_ANIMATION_H
#define SPENCER_ANIMATION_H

#include <Arduino.h>

class Matrix;

class MatrixAnim {
public:
	MatrixAnim(Matrix* matrix);
	virtual ~MatrixAnim();

	void start();
	void stop();
	virtual void reset() = 0;

	bool isStarted();

protected:
	Matrix* getMatrix();

	virtual void onStart() = 0;
	virtual void onStop() = 0;

private:
	Matrix* matrix;
	bool started = false;

};



#endif