#include "flex.h"

#include <Arduino.h>


// Calibration Values
int16_t cal_bend_val[10];
int16_t cal_straight_val[10];

// Input Values
int16_t flexValues[10];



// Setup for Flex-Sensors
void initFlex() {
  for(int i = 0; i < 10; i++) {
    pinMode(flex_pins[i], INPUT);
  }
}

// Measures the values for the Flex-Sensors
void readFlex() {

  for (int i = 0; i < 10; i++) {
    flexValues[i] = analogRead(flex_pins[i]);
    Serial.println(i + 1 + ": " + flexValues[i]);
  }
}

// Calibrates the range of the Flex-Sensors
void calibrateFlex() {

  for(int i = 0; i < 10; i++) {
    
  }
}