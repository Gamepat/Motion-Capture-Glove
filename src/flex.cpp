#include "flex.h"

#include <Arduino.h>


// Input Values
int16_t flexValues[10];



/* Measures the Values for the Flex-Sensors */
void readFlex() {

  for (int i = 0; i < 10; i++) {
    flexValues[i] = analogRead(flex_pins[i]);
    Serial.println(i + 1 + ": " + flexValues[i]);
  }
}



/* Setup for Flex-Sensors */
void initFlex() {
  for(int i = 0; i < 10; i++) {
    pinMode(flex_pins[i], INPUT);
  }
}