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
	MatrixAnimGIF(fs::FileImpl* file, Matrix* matrix = nullptr);
	~MatrixAnimGIF() override;

	GIF& getGIF();

	void reset() override;

	void loop(uint time);

	void push() override;

	float getCompletionPercentage();

	uint32_t getLoopDuration() const;

protected:
	void onStart() override;
	void onStop() override;

private:
	GIF gif;

	uint32_t frameTime = 0;
	uint32_t frameRemaining = 0;
	uint32_t startTime = 0;
	uint32_t totalDuration = 0;
};


#endif //CIRCUITOS_MATRIXANIMGIF_H
