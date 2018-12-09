#pragma once

#include <Arduino.h>

#define SENS_AMO 10

// Pin Definition (ADC0 - ADC10)
const uint8_t flex_pins[SENS_AMO] = {
  A0, A1, A2, A3, A4, A5, 4, 6, 8, 12
};


void initFlex();
void readFlex();