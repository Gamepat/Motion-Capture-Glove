#include <Arduino.h>

#include "lib/types.h"
#include "serial.h"
#include "flex.h"
#include "imu.h"


axis_float_t angles;


void setup() {
  serialInit();
  initFlex();

  imuInit();

}


void loop() {

  readFlex();

  readIMU(&angles);
  
}
