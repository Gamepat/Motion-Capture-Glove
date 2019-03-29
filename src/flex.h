#pragma once

#include <Arduino.h>

#define SENS_AMO 10

// Pin Definition (ADC0 - ADC10)
const uint8_t flex_pins[SENS_AMO] = {
  A8, A11, A6, A7, A1, A0, A3, A2, A5, A4
};


void initFlex();
void readFlex();