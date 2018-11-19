#pragma once
#include <Arduino.h>


#define BAUD 115200
#define BAUD_DEBUG 19200


void serialInit();
void serialSend(int16_t data, uint8_t port);
void serialSend(float data, uint8_t port);
void serialSend(String data, uint8_t port);