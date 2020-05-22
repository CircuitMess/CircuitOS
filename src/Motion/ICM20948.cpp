#include "ICM20948.h"
#include <cmath>

/**
 * SparkFun's ICM20948 library: https://github.com/sparkfun/SparkFun_ICM-20948_ArduinoLibrary/
 *
 * TODO: check license
 * https://github.com/sparkfun/SparkFun_ICM-20948_ArduinoLibrary/issues/16
 */
#include <ICM_20948.h>
#include "img_dmp3a_icm20948.h"

ICM20948::ICM20948(int sda, int scl) : sda(sda), scl(scl){ }

void ICM20948::calibrate(){
	MPU::calibrate();
	calibrateGyro(100);
	calibrateAccel(100);
}

bool ICM20948::readSensor(){
	return readICMData(false, true);
}

bool ICM20948::readICMData(bool waitReady, bool adjust){
	if(!icm->dataReady()){
		if(!waitReady) return false;

		while(!icm->dataReady()){
			delayMicroseconds(100); // sleep 100us
		}
	}

	auto data = icm->getAGMT();
	gyro = { (float) data.gyr.axes.x, (float) data.gyr.axes.y, (float) data.gyr.axes.z };
	accel = { (float) data.acc.axes.y, (float) data.acc.axes.x, (float) -data.acc.axes.z };
	magn = { (float) data.mag.axes.x, (float) data.mag.axes.y, (float) data.mag.axes.z };

	if(adjust){
		gyro.x = (gyro.x - gyroBias.x) * gyroScale;
		gyro.y = (gyro.y - gyroBias.y) * gyroScale;
		gyro.z = (gyro.z - gyroBias.z) * gyroScale;
		accel.x *= accelScale;
		accel.y *= accelScale;
		accel.z *= accelScale;
	}

	return true;
}

void ICM20948::begin(){
	Wire.begin(sda, scl);
	Wire.setClock(400000);
	ICM_20948_Status_e stat = icm->begin(Wire, false, ICM_20948_ARD_UNUSED_PIN);
	Serial.print(F("Startup returned: "));
	Serial.println(icm->statusString(stat));

	uint8_t data = 0b00000000;
	//icm->write(0x03, &data, 1);
	icm->swReset();
	delay(500);
	icm->sleep(false);
	delay(50);
	icm->lowPower(false);
	delay(50);

	load();
	load();
	load();

	stat = icm->enableDLPF(ICM_20948_Internal_Acc | ICM_20948_Internal_Gyr, true);
	Serial.print(F("Enable DLPF returned: "));
	Serial.println(icm->statusString(stat));

	/*ICM_20948_dlpcfg_t dlpcfg;
	dlpcfg.a = acc_d5bw7_n8bw3;
	dlpcfg.g = gyr_d361bw4_n376bw5;
	stat = icm->setDLPFcfg((ICM_20948_Internal_Acc | ICM_20948_Internal_Gyr), dlpcfg);
	Serial.print(F("DLPF configuration returned: "));
	Serial.println(icm->statusString(stat));*/
}

void ICM20948::calibrateGyro(uint8_t loops){
	Serial.println("Calibrating gyro");

	gyroScale = 0;
	gyroBias = { 0, 0, 0 };
	for(size_t i = 0; i < loops; i++){
		readICMData(true, false);
		for(int j = 0; j < 3; j++){
			gyroBias[j] += gyro[j] / (float) loops;
			gyroScale = max(fabs(gyroScale), fabs(gyro[j]));
		}
		delay(1);
	}

	gyroScale = 1.0f / (250.0f/32767.5f * (float) M_PI / 180.0f);

	Serial.printf("Bias: [ %.2f %.2f %.2f ]\n", gyroBias.x, gyroBias.y, gyroBias.z);
	Serial.printf("Scale: %.2f\n", gyroScale);
	gyroScale = 1.0f / gyroScale;
}

void ICM20948::calibrateAccel(uint8_t loops){
	Serial.println("Calibrating accel");

	accelScale = 0;

	for(int i = 0; i < loops; i++){
		readICMData(true, false);
		for(int j = 0; j < 3; j++){
			accelScale = max(fabs(accelScale), fabs(accel[j]));
		}
	}

	Serial.printf("Scale: %.2f\n", accelScale);
	accelScale = 1.0f / accelScale;
}

void ICM20948::load(){
#define DMP_LOAD_START 0x90
	Serial.printf("Loading DMP. Address %hhx, image size %lu bytes\n", DMP_LOAD_START, sizeof(dmp3a_icm20948));
	delay(10);

	ICM_20948_Status_e stat = ICM_20948_Stat_Ok;
	unsigned char* data = dmp3a_icm20948;
	size_t size = sizeof(dmp3a_icm20948);
	ushort addr = DMP_LOAD_START;
	unsigned char reg;
	unsigned char bank;
	size_t writeSize;
	unsigned char curBank = 0;
	icm->setBank(curBank);
	while(size > 0){
		writeSize = min((size_t) 1, size);
		if ((addr & 0xff) + writeSize > 0x100) {
			// Moved across a bank
			writeSize = (addr & 0xff) + writeSize - 0x100;
		}

		bank = (addr >> 8);
		if(bank != curBank){
			stat = icm->setBank(bank);
			if(stat != ICM_20948_Stat_Ok){
				Serial.printf("Erro switching to bank %d while writing. Addr %x, bank %d, register %hhx\n", bank, addr, bank, reg);
				Serial.println(icm->statusString(stat));
				return;
			}
			curBank = bank;
			delay(20);
		}

		if(bank == 1){
			break;
		}

		reg = (addr & 0xff);
		stat = icm->write(reg, data, writeSize);
		if(stat != ICM_20948_Stat_Ok){
			Serial.printf("Write error on addr %x, bank %d, register %hhx\n", addr, bank, reg);
			Serial.println(icm->statusString(stat));
			return;
		}

		byte retData[8];
		stat = icm->read(reg, retData, writeSize);
		if(stat != ICM_20948_Stat_Ok){
			Serial.printf("Auto Read error on addr %x, bank %d, register %hhx\n", addr, bank, reg);
			Serial.println(icm->statusString(stat));
			return;
		}

		for(int j = 0; j < writeSize; j++){
			if(retData[j] != data[j]){
				Serial.printf("[ERR] Auto data mismatch on byte %d! Expected %hhx, got %hhx\n", data - dmp3a_icm20948 + j, data[j], retData[j]);
				return;
			}
		}

		addr += writeSize;
		data += writeSize;
		size -= writeSize;
	}

	delay(10);

	addr = DMP_LOAD_START;
	data = dmp3a_icm20948;
	for(int i = 0; i < sizeof(dmp3a_icm20948); i++, addr++){
		byte bank = (addr >> 8);
		if(bank != curBank){
			stat = icm->setBank(bank);
			if(stat != ICM_20948_Stat_Ok){
				Serial.printf("Erro switching to bank %d while reading. Addr %x, bank %d, register %hhx\n", bank, addr, bank, reg);
				Serial.println(icm->statusString(stat));
				return;
			}
			curBank = bank;
			delay(20);
		}

		uint8_t data;
		reg = (addr & 0xff);
		stat = icm->read(reg, &data, 1);
		if(stat != ICM_20948_Stat_Ok){
			Serial.printf("Read error on addr %x, bank %d, register %hhx\n", addr, bank, reg);
			Serial.println(icm->statusString(stat));
			return;
		}

		if(data != dmp3a_icm20948[i]){
			Serial.printf("[ERR] Data mismatch on byte %d! Expected %hhx, got %hhx\n", i, dmp3a_icm20948[i], data);
			return;
		}
	}

	Serial.println("Data A-OK");
}
