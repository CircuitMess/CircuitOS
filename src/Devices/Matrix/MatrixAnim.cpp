#include "MatrixAnim.h"
#include "Matrix.h"

MatrixAnim::MatrixAnim(Matrix* matrix) : matrix(matrix){

}

MatrixAnim::~MatrixAnim(){
	stop();
}

void MatrixAnim::start(){
	if(started) return;
	started = true;

	onStart();
}

void MatrixAnim::stop(){
	if(!started) return;
	started = false;

	onStop();
}

bool MatrixAnim::isStarted(){
	return started;
}

Matrix* MatrixAnim::getMatrix(){
	return matrix;
}
