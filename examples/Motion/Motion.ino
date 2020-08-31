#include <Arduino.h>
#include <Wire.h>
#include <CircuitOS.h>
#include <Motion/vec.hpp>
#include <Util/Task.h>
#include <Display/Display.h>
#include <Loop/LoopManager.h>
#include <Motion/MPU6050_CM.h>
#include <Motion/ICM20948.h>

#define BTN_A 32
#define BTN_B 34
#define BTN_C 39
#define BTN_D 36

Display* display = new Display(128, 128, 18, 2);
Sprite* sprite = display->getBaseSprite();

MPU* mpu;
vec3f euler = { 0, 0, 0 };
vec3f accel = { 0, 0, 0 };
vec3f vel = { 0, 0, 0 };

void btnA(){

}

void printDisplay(){
	vel = { 0, 0, 0 };
	mpu->readSensor();
	vec3f _euler = mpu->getEuler();
	vec3f _accel = mpu->getAccel();


	sprite->clear(TFT_BLACK);
	sprite->setCursor(0, 0);

	sprite->println("\n Gyro");
	sprite->printf(" Pitch: %c%.2f rad\n", _euler.pitch < 0 ? '-' : ' ', fabs(_euler.pitch));
	sprite->printf(" Yaw:   %c%.2f rad\n", _euler.yaw < 0 ? '-' : ' ', fabs(_euler.yaw));
	sprite->printf(" Roll:  %c%.2f rad\n", _euler.roll < 0 ? '-' : ' ', fabs(_euler.roll));

	sprite->println("\n Accel");
	sprite->printf(" X:  %c%.2f m/s/s\n", _accel.x < 0 ? '-' : ' ', fabs(_accel.x));
	sprite->printf(" Y:  %c%.2f m/s/s\n", _accel.y < 0 ? '-' : ' ', fabs(_accel.y));
	sprite->printf(" Z:  %c%.2f m/s/s\n", _accel.z < 0 ? '-' : ' ', fabs(_accel.z));

	sprite->println("\n Velocity");
	sprite->printf(" X:  %c%.2f m/s\n", vel.x < 0 ? '-' : ' ', fabs(vel.x * 2000));
	sprite->printf(" Y:  %c%.2f m/s\n", vel.y < 0 ? '-' : ' ', fabs(vel.y * 2000));
	sprite->printf(" Z:  %c%.2f m/s\n", vel.z < 0 ? '-' : ' ', fabs(vel.z * 2000));

	display->commit();

	delay(25);
}

void displayTask(Task* task){
	while(task->running){
		printDisplay();
		delay(20);
	}
}

void setup(){
	Serial.begin(115200);

	/*new InputGPIO();
	Input::getInstance()->setBtnPressCallback(BTN_A, btnA);
	Input::getInstance()->start();*/

	sprite->clear(TFT_BLACK);
	sprite->setTextFont(1);
	sprite->setTextSize(1);
	sprite->setTextColor(TFT_WHITE);
	sprite->println("\n Calibrating...\n");
	display->commit();

	mpu = new MPU6050_CM(22, 21);
	mpu->begin();
	//mpu->calibrate();
	delay(100);

	Task dTask("DisplayTask", displayTask);
	dTask.start(2);
	//LoopManager::startTask();
}

void loop(){
	delay(500);
	//printDisplay();
	//LoopManager::loop();
	/*mpu->readSensor();
	euler = mpu->getEuler();
	accel = mpu->getAccel();
	Serial.printf("Euler/Accel: [ %.2f %.2f %.2f ], [ %.2f %.2f %.2f ]\n", euler.pitch, euler.yaw, euler.roll, accel.x, accel.y, accel.z);*/

	/*float pitch = atan2(-accel.x, -accel.z);
	float roll = -atan(-accel.y / sqrt(accel.x * accel.x + accel.z * accel.z));
	euler = { pitch, mpu->getEuler().yaw, roll };*/
	//euler = mpu->getEuler();

	/*vec3f grav = { 0, 0, -1 };
	quat<float> rot(euler);
	grav = rot.rotate(grav);
	grav.y *= -1;
	grav *= -1;
	accel += grav;*/

	//Serial.printf("Euler/Accel: [ %.2f %.2f %.2f ], [ %.2f %.2f %.2f ]\n", euler.pitch, euler.yaw, euler.roll, accel.x, accel.y, accel.z);
	//delay(20);
	//printDisplay();
}