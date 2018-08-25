#pragma once

#include <Arduino.h>
#include "lib/types.h"


#define CALIBRATION_PASSES 10000


#define GYRO_250D_SENS 131
#define ACCEL_2G_SENS 16384


// MPU 6000 / 6050 Registers
#define ACCEL_XOUT_H 	0x3B
#define GYRO_XOUT_H 	0x43
#define TEMP_OUT_H 		0x41


void mpu_init(int device_adr);
void mpu_readGyro(int device_adr, axis_int16_t *gyro_data);
void mpu_readAccel(int device_adr, axis_int16_t *accel_data);
void mpu_calibrateGyro(int device_adr, axis_int16_t *offset);
void mpu_calibrateAccel(int device_adr, axis_int16_t *offset);