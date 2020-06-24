#ifndef CIRCUITOS_MPUFUSION_H
#define CIRCUITOS_MPUFUSION_H


#include "../Update/UpdateListener.h"
#include "MPU.h"

class MPUFusion : public MPU, public UpdateListener {
public:
	explicit MPUFusion(MPU* mpu);

	void update(uint millis) override;

	bool readSensor() override;
	void begin() override;
	void calibrate() override;

private:
	MPU* mpu = nullptr;

	const uint pollT = 1000 / 500; // in ms
	const uint stepRate = 2;
	const uint stepT = pollT / stepRate;
	uint time = 0;
	uint calced = 0;

	vec3f gravity = { 0, 0, 0 };

	void calc();
	void poll();

	vec3f tmpEuler = { 0, 0, 0 };
	vec3f tmpGyro = { 0, 0, 0 };
	vec3f tmpAccel = { 0, 0, 0 };
	vec3f tmpMagn = { 0, 0, 0 };
};


#endif //CIRCUITOS_MPUFUSION_H
