#pragma once

#include <Arduino.h>

#define DEBUG 0
#define BT 1

typedef struct {
  int16_t x, y, z;
} axis_int16_t;

typedef struct {
  int32_t x, y, z;
} axis_int32_t;

typedef struct {
  float x, y, z;
} axis_float_t;

typedef struct {
  double x, y, z;
} axis_double_t;