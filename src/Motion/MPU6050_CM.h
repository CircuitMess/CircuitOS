#ifndef CIRCUITOS_MPU6050_CM_H
#define CIRCUITOS_MPU6050_CM_H


#include "MPU.h"

class MPU6050;

class MPU6050_CM : public MPU {
public:
	MPU6050_CM(int sda, int scl);

	bool readSensor() override;
	void begin() override;
	void calibrate() override;

	void calibrateGyro(uint8_t loops = 100);
	void calibrateAccel(uint8_t loops = 100);

private:
	int sda = -1;
	int scl = -1;
	float accelScale = 1;
	float gyroScale = 1;
	vec3f gyroBias = { 0, 0, 0 };

	MPU6050* mpu = nullptr;

	bool readData(bool waitReady = false, bool adjust = true);
};


#endif //CIRCUITOS_MPU6050_CM_H
