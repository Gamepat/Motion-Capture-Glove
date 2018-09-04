#include "serial.h"

#include <Arduino.h>
#include <Wire.h>


void serialInit() {
  Serial1.begin(BAUD);
  Serial.begin(BAUD_DEBUG);
}