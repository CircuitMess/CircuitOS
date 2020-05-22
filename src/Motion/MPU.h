// Courtesy of https://github.com/kriswiner/MPU9250

#ifndef SETTINGS_MPU_H
#define SETTINGS_MPU_H

#include <Arduino.h>
#include "vec.hpp"

class MPU {
public:
	virtual bool readSensor() = 0;
	virtual void begin() = 0;
	virtual void calibrate();

	virtual const vec3f& getEuler() const;
	virtual const quatf& getQuat() const;
	virtual const vec3f& getGyro() const;
	virtual const vec3f& getAccel() const;
	virtual const vec3f& getMagn() const;
	virtual const vec3f& getVelocity() const;


protected:
	vec3f euler;
	quatf quatRot;
	vec3f gyro;
	vec3f accel;
	vec3f magn;
	vec3f velocity;


};


#endif //SETTINGS_MPU_H
