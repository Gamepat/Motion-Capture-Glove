#include "imu.h"
#include "lib/types.h"
#include "mpu.h"

#include <Arduino.h>
#include <Wire.h>



axis_int16_t gyro_raw;
axis_int16_t accel_raw;

axis_int16_t gyro_offset;
axis_int16_t accel_offset;

axis_float_t rates;
axis_float_t accel;

axis_float_t accel_angles;

axis_float_t angles;


float last_update = 0.0;



void imuInit() {
	mpu_init(MPU_ADR_1);
	mpu_calibrateGyro(MPU_ADR_1, &gyro_offset);
	mpu_calibrateAccel(MPU_ADR_1, &accel_offset);
}


void readGyro() {
	mpu_readGyro(MPU_ADR_1, &gyro_raw);
}

void readAccel() {
	mpu_readAccel(MPU_ADR_1, &accel_raw);
}


void processGyro() {
	rates.x = (float)(gyro_raw.x - gyro_offset.x) / GYRO_250D_SENS;
	rates.y = (float)(gyro_raw.y - gyro_offset.y) / GYRO_250D_SENS;
	rates.z = (float)(gyro_raw.z - gyro_offset.z) / GYRO_250D_SENS;
}

void processAccel() {
	accel.x = (float)(accel_raw.x - accel_offset.x) / ACCEL_2G_SENS;
	accel.y = (float)(accel_raw.y - accel_offset.y) / ACCEL_2G_SENS;
	accel.z = (float)(accel_raw.z - accel_offset.z) / ACCEL_2G_SENS;
}


void calculateAngles() {

	// TODO: Replace this with the Madgwick-Algorithm

	float dt = (float)((micros() - last_update) / 1000000);
	last_update = micros();

	accel_angles.x = atan2(accel.y, accel.z) * RAD_TO_DEG;
	accel_angles.y = atan2(-1 * accel.x, sqrt(accel.y * accel.y + accel.z * accel.z)) * RAD_TO_DEG;

	angles.x = GYRO_PART * (angles.x + (rates.x * dt)) + ACCEL_PART *accel_angles.x;
	angles.y = GYRO_PART * (angles.y + (rates.y * dt)) + ACCEL_PART *accel_angles.y;
	//angles.z = GYRO_PART * (angles.z + (rates.z * dt)) + ACCEL_PART *accel_angles.z;		//FIXME
}


void readIMU(axis_float_t *rot_angles) {
	readGyro();
	readAccel();

	processGyro();
	processAccel();

	calculateAngles();

	rot_angles->x = angles.x;
	rot_angles->y = angles.y;
	rot_angles->z = angles.z;
}