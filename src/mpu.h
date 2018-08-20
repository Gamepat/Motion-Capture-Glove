#pragma once

#include <Arduino.h>



// MPU 6000 / 6050 Registers
#define ACCEL_XOUT_H 	0x3B
#define GYRO_XOUT_H 	0x43
#define TEMP_OUT_H 		0x41


void mpu_readGyro(int device_adr, axis_int16_t *gyro_data);
void mpu_readAccel(int device_adr, axis_int16_t *accel);