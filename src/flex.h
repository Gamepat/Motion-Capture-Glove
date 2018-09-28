#pragma once

#include <Arduino.h>



// Pin Definition (ADC0 - ADC10)
const uint8_t flex_pins[10] = {
  A5, A4, A3, A2, A1, A0, 4, 12, 6, 8
};


void initFlex();
void readFlex();
void calibrateFlex();