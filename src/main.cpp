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


/* Values for Gyro 1 */
// Adresses
const int MPU_ADR1 = 0x68;

// Input Values
int32_t acX, acY, acZ;

// Output Values
int16_t aX, aY, aZ;

// Set Values
int16_t acXset_min, acXset_max;
int16_t acYset_min, acYset_max;
int16_t acZset_min, acZset_max;




/* Setup for Flex-Sensors */
void initFlex() {
  for(int i = 0; i < 10; i++) {
    pinMode(sensors[i], INPUT);
  }
}


/* Setup for Accelerometer */
void initGyro() {
  Wire.begin();
  Wire.beginTransmission(MPU_ADR1);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

/* Measures the Values for the Flex-Sensors */
void readFlex() {

  for (int i = 0; i < 10; i++) {
    flexValues[i] = analogRead(sensors[i]);
    Serial.println(i + 1 + ": " + flexValues[i]);
  }
}

/* Measures the ACC-Values "PASSES"-Times and calculates the arithmetic mean */
void readGyro() {

  // Resets ac-Values
  acX = 0;
  acY = 0;
  acZ = 0;

  for (int i = 0; i < PASSES; i++) {
    Wire.beginTransmission(MPU_ADR1);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADR1, 6, true);
    acX += Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    acY += Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    acZ += Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    delay(1);
  }

  acX /= PASSES;
  acY /= PASSES;
  acZ /= PASSES;
}


void sendData() {
  
}



void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
  initFlex();
  initGyro();
}


void loop() {
  
  readGyro();
  Serial.print("\n");
  Serial.print("AcX = "); Serial.print(acX);
  Serial.print(" | AcY = "); Serial.print(acY);
  Serial.print(" | AcZ = "); Serial.print(acZ);
  delay(100);

}
