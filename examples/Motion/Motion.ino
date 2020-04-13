#include <Arduino.h>
#include <CircuitOS.h>
#include <Update/UpdateManager.h>
#include <Display/Display.h>
#include <Motion/MPU9250.h>
#include <Util/Settings.h>
#include <Input/InputGPIO.h>

#define BTN_A 32
#define BTN_B 34
#define BTN_C 39
#define BTN_D 36

MPU* mpu;
Display display(128, 128, 18, 4);
Sprite* sprite = display.getBaseSprite();

struct MagCal {
	vec3f bias;
	vec3f scale;
};

MagCal* settings(){
	return static_cast<MagCal*>(Settings::data());
}

void btnA(){
	mpu->resetVelocity();
};

void setup(){
	Serial.begin(115200);
	Settings::init(new MagCal(), sizeof(MagCal));

	new InputGPIO();
	Input::getInstance()->setBtnPressCallback(BTN_A, btnA);

	sprite->clear(TFT_BLACK);

	sprite->setTextFont(1);
	sprite->setTextSize(1);
	sprite->setTextColor(TFT_WHITE);

	sprite->println("\n Calibrating...\n");
	display.commit();

	MPU9250* _mpu = new MPU9250();
	mpu = _mpu;
	mpu->begin();
	_mpu->calibrateAK();

	Input::getInstance()->start();

	return;

	MagCal* cal = settings();
	if(cal->scale.x == 0){
		_mpu->calibrateAK();
		*cal = { _mpu->getMagBias(), _mpu->getMagScale() };
		Settings::store();
	}else{
		_mpu->setMag(cal->bias, cal->scale);
	}
}

void loop(){
	mpu->readSensor();
	vec3f euler = mpu->getEuler();
	vec3f accel = mpu->getAccel();
	vec3f vel = mpu->getVelocity();

	sprite->clear(TFT_BLACK);
	sprite->setCursor(0, 0);

	sprite->println("\n Gyro");
	sprite->printf(" Pitch: %c%.2f rad\n", euler.pitch < 0 ? '-' : ' ', fabs(euler.pitch));
	sprite->printf(" Yaw:   %c%.2f rad\n", euler.yaw< 0 ? '-' : ' ', fabs(euler.yaw));
	sprite->printf(" Roll:  %c%.2f rad\n", euler.roll < 0 ? '-' : ' ', fabs(euler.roll));

	sprite->println("\n Accel");
	sprite->printf(" X:  %c%.2f m/s/s\n", accel.x < 0 ? '-' : ' ', fabs(accel.x));
	sprite->printf(" Y:  %c%.2f m/s/s\n", accel.y < 0 ? '-' : ' ', fabs(accel.y));
	sprite->printf(" Z:  %c%.2f m/s/s\n", accel.z < 0 ? '-' : ' ', fabs(accel.z));

	sprite->println("\n Velocity");
	sprite->printf(" X:  %c%.2f m/s\n", vel.x < 0 ? '-' : ' ', fabs(vel.x * 2000));
	sprite->printf(" Y:  %c%.2f m/s\n", vel.y < 0 ? '-' : ' ', fabs(vel.y * 2000));
	sprite->printf(" Z:  %c%.2f m/s\n", vel.z < 0 ? '-' : ' ', fabs(vel.z * 2000));

	display.commit();
}