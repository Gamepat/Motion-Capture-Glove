#pragma once

#include <Arduino.h>



// Pin Definition (ADC0 - ADC10)
const uint8_t flex_pins[10] = {
  A0, A1, A2, A3, A4, A5, 4, 6, 8, 12
};


void initFlex();
void readFlex();
void calibrateFlex();