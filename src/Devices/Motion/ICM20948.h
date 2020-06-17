#ifndef CIRCUITOS_ICM20948_H
#define CIRCUITOS_ICM20948_H

#include "../../Motion/MPU.h"

class ICM_20948_I2C;

class ICM20948 : public MPU {
public:
	explicit ICM20948(int sda, int scl);

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

	ICM_20948_I2C* icm = nullptr;

	bool readICMData(bool waitReady = false, bool adjust = true);
	void load();
};


#endif //CIRCUITOS_ICM20948_H
