#include "mpu.h"
#include "lib/types.h"

#include <Arduino.h>
#include <Wire.h>



void mpu_readGyro(int device_adr, axis_int16_t *gyro_data) {
	Wire.beginTransmission(device_adr);
	Wire.write(GYRO_XOUT_H);
	Wire.endTransmission(false);
	Wire.requestFrom(device_adr, 6, true);		//request 6 bytes from device
	
  int16_t gyro_x = Wire.read() << 8 | Wire.read();
	int16_t gyro_y = Wire.read() << 8 | Wire.read();
	int16_t gyro_z = Wire.read() << 8 | Wire.read();

  gyro_data->x = gyro_x;
  gyro_data->y = gyro_y;
  gyro_data->z = gyro_z;
}


void mpu_readAccel(int device_adr, axis_int16_t *accel) {
	Wire.beginTransmission(device_adr);
	Wire.write(ACCEL_XOUT_H);
	Wire.endTransmission(false);
	Wire.requestFrom(device_adr, 6, true);		//request 6 bytes from device

	int16_t accel_x = Wire.read() << 8 | Wire.read();
	int16_t accel_y= Wire.read() << 8 | Wire.read();
	int16_t accel_z= Wire.read() << 8 | Wire.read();

  accel->x = accel_x;
  accel->y = accel_y;
  accel->z = accel_z;
}