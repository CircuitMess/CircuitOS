// Courtesy of https://github.com/kriswiner/MPU9250

#ifndef SETTINGS_MPU_H
#define SETTINGS_MPU_H

#include <Arduino.h>
#include "vec.hpp"

class MPU {
public:
	virtual void readSensor();
	virtual void calibrate();
	virtual void begin() = 0;

	virtual const vec3f getEuler() const;
	virtual const vec3f& getGyro() const;
	virtual const vec3f& getAccel() const;
	virtual const vec3f& getMagn() const;
	virtual const vec3f& getVelocity() const;

	void resetVelocity();

protected:
	vec3f gyro;
	vec3f accel;
	vec3f magn;

private:
	vec3f euler;
	vec3f velocity;
	uint lastMicros = 0;
	vec4f quat;

	vec3f gravity = { 0, 0, 0 };
	vec3f lastAccel = { 0, 0, 0 };
	vec3f lastJerk = { 0, 0, 0 };
	int i = 0;
};


#endif //SETTINGS_MPU_H
