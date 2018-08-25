#pragma once

#include <Arduino.h>


#define MPU_ADR_1 0x68
#define MPU_ADR_2 0x69


#define GYRO_250D_SENS 131
#define ACCEL_2G_SENS 16384

#define GYRO_PART 0.995
#define ACCEL_PART (1 - GYRO_PART)


void imuInit();