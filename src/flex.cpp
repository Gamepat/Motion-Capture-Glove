#include "flex.h"

#include <Arduino.h>


// Calibration Values
int16_t cal_bend_val[SENS_AMO];
int16_t cal_straight_val[SENS_AMO];

// Input Values
int16_t flexValues[SENS_AMO];

// Output Values
int16_t flexAngles[SENS_AMO];


// Function Prototypes
void calibrateFlex();


// Setup for Flex-Sensors
void initFlex() {
  // set the Arduino pins to INPUT
  for(int i = 0; i < 10; i++) {
    pinMode(flex_pins[i], INPUT);
    delay(1);
  }

  calibrateFlex();
  Serial1.println();
}


// Measures the values for the flex-Sensors
void getRawFlex() {
  for (int i = 0; i < 10; i++) {
    flexValues[i] = analogRead(flex_pins[i]);
    delay(3);
    Serial1.print(i+1);
    Serial1.print(": ");
    Serial1.println(flexValues[i]);
  }
}


// Map the input values to get an angle
void calcFlex() {
  for(int i = 0; i < 10; i++) {
    flexAngles[i] = map(flexValues[i], cal_straight_val[i], cal_bend_val[i], 0, 90);
    delay(1);
  }
}


// Read the flex-sensors and convert the raw values into angles
void readFlex() {
  getRawFlex();
  calcFlex();
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