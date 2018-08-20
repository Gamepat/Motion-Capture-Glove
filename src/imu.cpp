#include "imu.h"
#include "lib/types.h"
#include "mpu.h"

#include <Arduino.h>
#include <Wire.h>



axis_int16_t gyro_raw;
axis_int16_t accel_raw;

float gyro_dt;
float dt;



void imuInit() {
	
}

void readGyro() {
	mpu_readGyro(MPU_ADR_1, &gyro_raw);
}

void readAccel() {
	mpu_readAccel(MPU_ADR_1, &accel_raw);
}





void processGyro() {

}