#include <Arduino.h>
#include <Wire.h>

#include "lib/types.h"

#define PASSES 5




/* Values for Flex-Sensors */
// Pin Definition (ADC0 - ADC10)
int sensors[10] = {
  A5, A4, A3, A2, A1, A0, 4, 12, 6, 8
};

// Input Values
int16_t flexValues[10];




/* Setup for Flex-Sensors */
void initFlex() {
  for(int i = 0; i < 10; i++) {
    pinMode(sensors[i], INPUT);
  }
}



/* Measures the Values for the Flex-Sensors */
void readFlex() {

  for (int i = 0; i < 10; i++) {
    flexValues[i] = analogRead(sensors[i]);
    Serial.println(i + 1 + ": " + flexValues[i]);
  }
}



void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
  
}


void loop() {
  

}
