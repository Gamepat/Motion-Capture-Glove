#pragma once

#include <Arduino.h>
#include "lib/types.h"

#define OFFSET_G_X 38
#define OFFSET_G_Y -112
#define OFFSET_G_Z 72
#define OFFSET_A_Z 1230

#define INTERRUPT_PIN 7


void setupI2Cdev();
void loopI2Cdev(axis_float_t *return_angles);