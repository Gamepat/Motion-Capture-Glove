#pragma once

#include <Arduino.h>

#define DEBUG 0
#define BT 1

typedef struct {
  int16_t x, y, z;
} axis_int16_t;

typedef struct {
  float x, y, z;
} axis_float_t;