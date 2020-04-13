#include "MPU.h"
#include "../Update/UpdateManager.h"
#include <Wire.h>
#include "Fusion.hpp"

void MPU::calibrate(){
	euler = { 0, 0, 0 };
	quat = { 1, 1, 1, 0 };
	velocity = { 0, 0, 0 };
}

void MPU::resetVelocity(){
	velocity = { 0, 0, 0 };
}

void MPU::readSensor(){
	uint m = micros();

	if(lastMicros == 0){
		lastMicros = m;
		return;
	}

	float lastMMicros = lastMicros;

	float dt = (float) (m - lastMicros) / 1000000.0f;
	lastMicros = m;

	// magn = { 1, 0, 0 };
	for(int i = 0; i < 5; i++){
		m = micros();
		float mdt = (float) (m - lastMMicros) / 1000000.0f;
		lastMMicros = m;

		float _mdt = dt / 5;

		MadgwickQuaternionUpdate(quat, _mdt, sqrt(3.0f / 4.0f) * PI * (40.0f / 180.0f),
								 accel.x, accel.y, accel.z,
								 gyro.pitch, gyro.yaw, gyro.roll,
								 magn.x, magn.y, magn.z);
	}


	euler.pitch  = atan2(2.0f * (quat[0] * quat[1] + quat[2] * quat[3]), quat[0] * quat[0] - quat[1] * quat[1] - quat[2] * quat[2] + quat[3] * quat[3]);
	euler.yaw = atan2(2.0f * (quat[1] * quat[2] + quat[0] * quat[3]), quat[0] * quat[0] + quat[1] * quat[1] - quat[2] * quat[2] - quat[3] * quat[3]);
	euler.roll = -asin(2.0f * (quat[1] * quat[3] - quat[0] * quat[2]));
	euler.yaw   -= 0.0f ; // Declination at Danville, California is 13 degrees 48 minutes and 47 seconds on 2014-04-04

	// accel.x += 1.0f * sin(euler.roll);
	// accel.y -= 1.0f * sin(euler.pitch);
	//accel.z -= 1.0f * (cos(euler.pitch) * sin(euler.roll) + cos(euler.roll) * sin(euler.pitch));

	/*float o = 0.9f;
	gravity.x = o * gravity.x + (1.0f - o) * accel.x;
	gravity.y = o * gravity.y + (1.0f - o) * accel.y;
	gravity.z = o * gravity.z + (1.0f - o) * accel.z;

	accel.x -= gravity.x;
	accel.y -= gravity.y;
	accel.z -= gravity.z;*/

	velocity.x += accel.x * dt;
	velocity.y += accel.y * dt;
	velocity.z += accel.z * dt;
}

const vec3f MPU::getEuler() const {
	return euler;
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

