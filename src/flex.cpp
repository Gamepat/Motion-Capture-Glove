#include "flex.h"

#include <Arduino.h>


// Calibration Values
int16_t cal_bend_val[SENS_AMO];
int16_t cal_straight_val[SENS_AMO];

// Input Values
int16_t flexValues[SENS_AMO];

// Output Values
int16_t flexAngles[SENS_AMO];


// Setup for Flex-Sensors
void initFlex() {
  for(int i = 0; i < 10; i++) {
    pinMode(flex_pins[i], INPUT);
  }
  Serial.println();
}


// Measures the values for the Flex-Sensors
void readRawFlex() {
  for (int i = 0; i < 10; i++) {
    flexValues[i] = analogRead(flex_pins[i]);
    Serial.print(i+1);
    Serial.print(": ");
    Serial.println(flexValues[i]);
  }
}


// Map the input values to get an angle
void calcFlex() {
  for(int i = 0; i < 10; i++) {
    flexAngles[i] = map(flexValues[i], cal_straight_val[i], cal_bend_val[i], 0, 90);
  }
}


// Calibrates the range of the Flex-Sensors
void calibrateFlex() {
  Serial.println("Calibration started.");

  // Measures closed hand values
  Serial.println("Close your hand to start.");
  delay(10000);
  for(int i = 0; i < 10; i++) {
    cal_bend_val[i] = analogRead(flex_pins[i]);
    delay(5);
  }
  Serial.println("Measured!");
  delay(3000);

  // Measures opened hand values
  Serial.println("Open your hand as straight as possible.");
  delay(10000);
  for(int i = 0; i < 10; i++) {
    cal_straight_val[i] = analogRead(flex_pins[i]);
    delay(5);
  }
  Serial.println("Finished!");
}