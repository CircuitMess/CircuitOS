#include "MPU.h"

void MPU::calibrate(){
	euler = { 0, 0, 0 };
	velocity = { 0, 0, 0 };
}

const vec3f& MPU::getEuler() const {
	return euler;
}

const quatf& MPU::getQuat() const{
	return quatRot;
}

const vec3f& MPU::getGyro() const{
	return gyro;
}

const vec3f& MPU::getAccel() const{
	return accel;
}

const vec3f& MPU::getMagn() const{
	return magn;
}

const vec3f& MPU::getVelocity() const{
	return velocity;
}

