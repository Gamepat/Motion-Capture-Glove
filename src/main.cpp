#include <Arduino.h>

#include "lib/types.h"
#include "serial.h"
#include "flex.h"
#include "imu.h"


axis_float_t angle;


void setup() {
  serialInit();
  initFlex();

  imuInit();
}


void loop() {

  readFlex();
  readIMU(&angle);

  Serial.println(angle.x);
  Serial.println(angle.y);
  Serial.println(angle.z);

  delay(10);
}