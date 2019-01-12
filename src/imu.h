#pragma once

#include <Arduino.h>
#include "lib/types.h"
#include "mpu.h"


#define MPU_ADR_1 0x69
#define MPU_ADR_2 0x69

#define GYRO_SENS GYRO_250D_SENS
#define ACCEL_SENS ACCEL_2G_SENS


#define GYRO_PART 0.995
#define ACCEL_PART (1 - GYRO_PART)


void imuInit();
void readIMU(axis_float_t *rot_angles);