#pragma once

#include <Arduino.h>
#include "lib/types.h"


#define MPU_ADR_1 0x68
#define MPU_ADR_2 0x69




#define GYRO_PART 0.995
#define ACCEL_PART (1 - GYRO_PART)


void imuInit();
void readIMU(axis_float_t *rot_angles);