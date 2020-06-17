#include "MPUFusion.h"
#include "Fusion.hpp"

MPUFusion::MPUFusion(MPU* mpu, Mutex& mutex) : mpu(mpu), mutex(mutex){ }

void MPUFusion::begin(){
	mpu->begin();
}

void MPUFusion::calibrate(){
	MPU::calibrate();
	quatRot = { 1, 1, 1, 0 };
	mpu->calibrate();
}

bool MPUFusion::readSensor(){
	return true;
}

void MPUFusion::update(uint millis){
	time += millis;

	if(time >= pollT * 1000){
		//Serial.printf("Polling after %.2f ms, %.2fHz\n", (float) time / 1000.0f, 1000000.f / time);

		/*while(calced < stepRate){
			calc();
			calced++;
		}*/

		poll();
		time = 0;
		calced = 0;
	}

	/*if(time >= calced * stepT){
		calc();
		calced++;
	}*/
}

uint lastm = 0;
void MPUFusion::poll(){
	uint d = micros() - lastm;
	lastm = micros();
	//Serial.printf("Polling after %.2fms, f = %.2fHz\n", (float) d / 1000.0f, 1000000.0f / d);

	mpu->readSensor();
	tmpAccel = mpu->getAccel();
	tmpGyro = mpu->getGyro();
	tmpMagn = mpu->getMagn();

	for(int i = 0; i < stepRate; i++){
		calc();
	}

	mutex.lock();
	accel = tmpAccel;
	gyro = tmpGyro;
	magn = tmpMagn;
	euler = tmpEuler;
	mutex.unlock();
}

void MPUFusion::calc(){
	vec4f quat;
	MadgwickQuaternionUpdate(quat, (float) stepT / 1000.0f, sqrt(3.0f / 4.0f) * PI * (40.0f / 180.0f),
			-tmpAccel.y, tmpAccel.x, -tmpAccel.z,
			tmpGyro.pitch, tmpGyro.yaw, tmpGyro.roll,
			tmpMagn.x, tmpMagn.y, tmpMagn.z);


	tmpEuler.pitch  = -atan2(2.0f * (quat[0] * quat[1] + quat[2] * quat[3]), quat[0] * quat[0] - quat[1] * quat[1] - quat[2] * quat[2] + quat[3] * quat[3]);
	tmpEuler.yaw = atan2(2.0f * (quat[1] * quat[2] + quat[0] * quat[3]), quat[0] * quat[0] + quat[1] * quat[1] - quat[2] * quat[2] - quat[3] * quat[3]);
	tmpEuler.roll = -asin(2.0f * (quat[1] * quat[3] - quat[0] * quat[2]));
	tmpEuler.yaw   -= 0.0f ; // Declination at Danville, California is 13 degrees 48 minutes and 47 seconds on 2014-04-04

	// TODO: check if fusion function assumes quat[0] is w component
	this->quatRot = { quat[0], quat[1], quat[2], quat[3] };

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

	/*velocity.x += accel.x * dt;
	velocity.y += accel.y * dt;
	velocity.z += accel.z * dt;*/
}