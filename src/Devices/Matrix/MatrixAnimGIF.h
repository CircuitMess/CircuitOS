#ifndef CIRCUITOS_MATRIXANIMGIF_H
#define CIRCUITOS_MATRIXANIMGIF_H

#include <Arduino.h>
#include <FS.h>
#include "MatrixAnim.h"
#include "../../Util/GIF.h"
#include "../../Loop/LoopListener.h"

class MatrixAnimGIF : public MatrixAnim, public LoopListener {
public:
	MatrixAnimGIF(Matrix* matrix, fs::File file);

	GIF& getGIF();

	void reset() override;

	void loop(uint time);

protected:
	void onStart() override;
	void onStop() override;

private:
	GIF gif;

	uint32_t frameTime = 0;
	uint32_t frameRemaining = 0;

	void pushFrame();

};


#endif //CIRCUITOS_MATRIXANIMGIF_H
