#ifndef CIRCUITOS_MATRIXANIMGIF_H
#define CIRCUITOS_MATRIXANIMGIF_H

#include <Arduino.h>
#include <FS.h>
#include "MatrixAnim.h"
#include "../../Util/GIF.h"
#include "../../Loop/LoopListener.h"

class MatrixAnimGIF : public MatrixAnim, public LoopListener {
public:
	MatrixAnimGIF(fs::File file, Matrix* matrix = nullptr);
	~MatrixAnimGIF() override;

	GIF& getGIF();

	void reset() override;

	void loop(uint time);

	void push() override;

protected:
	void onStart() override;
	void onStop() override;

private:
	GIF gif;

	uint32_t frameTime = 0;
	uint32_t frameRemaining = 0;
};


#endif //CIRCUITOS_MATRIXANIMGIF_H
