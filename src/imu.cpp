#include "imu.h"
#include "lib/types.h"
#include "mpu.h"

#include <Arduino.h>
#include <Wire.h>


bool started = false;

axis_int16_t gyro_raw;
axis_int16_t accel_raw;

axis_int16_t gyro_offset = {-143, 437, -268};
axis_int16_t accel_offset = {968, -66, -588};

axis_float_t rates;
axis_float_t accel;

float tot_vect;
axis_float_t gyro_angles;
axis_float_t accel_angles;

axis_float_t angles;


float last_update = 0.0;


// initialize the IMU and run calibration
void imuInit() {
	mpu_init(MPU_ADR_1);

	Serial.println("Started calibration");
	mpu_calibrateGyro(MPU_ADR_1, &gyro_offset);
	mpu_calibrateAccel(MPU_ADR_1, &accel_offset);
}


void readGyro() {
	mpu_readGyro(MPU_ADR_1, &gyro_raw);
}

void readAccel() {
	mpu_readAccel(MPU_ADR_1, &accel_raw);
}


// converts the 16Bit raw value into °/s
void processGyro() {
	rates.x = (float)(gyro_raw.x - gyro_offset.x) / GYRO_250D_SENS;
	rates.y = (float)(gyro_raw.y - gyro_offset.y) / GYRO_250D_SENS;
	rates.z = (float)(gyro_raw.z - gyro_offset.z) / GYRO_250D_SENS;
}

// converts the 16Bit raw value into multiples of 1g
void processAccel() {
	accel.x = (float)(accel_raw.x - accel_offset.x) / ACCEL_2G_SENS;
	accel.y = (float)(accel_raw.y - accel_offset.y) / ACCEL_2G_SENS;
	accel.z = (float)(accel_raw.z - accel_offset.z) / ACCEL_2G_SENS;
}


// calculates angles from the gyroscope data
void calcGyroAngles() {
	float dt = (float)(micros() - last_update) / 1000000.0;			// calculates the time since last measurement in seconds

	gyro_angles.x += rates.x * dt;
	gyro_angles.y += rates.y * dt;
	gyro_angles.z += rates.z * dt;

	last_update = micros();

	// gyro_angles.x += gyro_angles.y * sin(rates.z * dt * DEG_TO_RAD);
	// gyro_angles.y -= gyro_angles.x * sin(rates.z * dt * DEG_TO_RAD);
}

// calculates angles from the accelerometer data
void calcAccelAngles() {
	accel_angles.x = atan2(accel.y, accel.z) * RAD_TO_DEG;
	accel_angles.y = atan2(-1 * accel.x, sqrt(accel.y * accel.y + accel.z * accel.z)) * RAD_TO_DEG;
}


// combines the two previous calculated angles to get a more stable output
void calculateAngles() {

	// use the angles calculated from the accelerometer data for startup, then switch to the complementary filter
	if (started) {
		angles.x = GYRO_PART * gyro_angles.x + ACCEL_PART * accel_angles.x;
		angles.y = GYRO_PART * gyro_angles.y + ACCEL_PART * accel_angles.y;
		// angles.z = GYRO_PART * gyro_angles.z + ACCEL_PART * accel_angles.z;		//FIXME
	}
	else {
		angles.x = accel_angles.x;
		angles.y = accel_angles.y;
		angles.z = accel_angles.z;

		started = true;
	}
}


void readIMU(axis_float_t *rot_angles) {
	readGyro();
	readAccel();

	processGyro();
	processAccel();

	calcGyroAngles();
	calcAccelAngles();
	calculateAngles();

	rot_angles->x = angles.x;
	rot_angles->y = angles.y;
	rot_angles->z = angles.z;
}