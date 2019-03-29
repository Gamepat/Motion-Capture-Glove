#include "serial.h"
#include "lib/types.h"


void serialInit() {
  Serial1.begin(BAUD);
  Serial.begin(BAUD_DEBUG);
}

void serialSend(int16_t data, uint8_t port) {
  switch(port){
    case 0: Serial.println(data); break;
    case 1: Serial1.println(data); break;
    default: break;
  }
}

void serialSend(float data, uint8_t port) {
  switch(port){
    case 0: Serial.println(data); break;
    case 1: Serial1.println(data); break;
    default: break;
  }
}

void serialSend(String data, uint8_t port) {
  switch(port){
    case 0: Serial.println(data); break;
    case 1: Serial1.println(data); break;
    default: break;
  }
}