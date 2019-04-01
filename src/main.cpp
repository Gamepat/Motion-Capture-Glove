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
  
  serialSend(angle.x, BT);
  serialSend(angle.y, BT);
  serialSend(angle.z, BT);

  serialSend("e", BT);

  delay(10);
}