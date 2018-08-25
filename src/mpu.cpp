#include "mpu.h"
#include "lib/types.h"

#include <Arduino.h>
#include <Wire.h>




void mpu_init(int device_adr) {
	Wire.begin();
  Wire.beginTransmission(device_adr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}


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


void mpu_readAccel(int device_adr, axis_int16_t *accel_data) {
	Wire.beginTransmission(device_adr);
	Wire.write(ACCEL_XOUT_H);
	Wire.endTransmission(false);
	Wire.requestFrom(device_adr, 6, true);		//request 6 bytes from device

	int16_t accel_x = Wire.read() << 8 | Wire.read();
	int16_t accel_y = Wire.read() << 8 | Wire.read();
	int16_t accel_z = Wire.read() << 8 | Wire.read();

  accel_data->x = accel_x;
  accel_data->y = accel_y;
  accel_data->z = accel_z;
}


void mpu_calibrateGyro(int device_adr, axis_int16_t *offset) {
	axis_int16_t gyro_raw;
	axis_float_t gyro_sum;

	for(int i = 0; i < CALIBRATION_PASSES; i++) {
		mpu_readGyro(device_adr, &gyro_raw);
		gyro_sum.x += gyro_raw.x;
		gyro_sum.y += gyro_raw.y;
		gyro_sum.z += gyro_raw.z;
	}

	offset->x = (int16_t)gyro_sum.x / CALIBRATION_PASSES;
	offset->y = (int16_t)gyro_sum.y / CALIBRATION_PASSES;
	offset->z = (int16_t)gyro_sum.z / CALIBRATION_PASSES;

	Serial.println("Gyro-Calibration finished.");
	Serial.println(gyro_sum.x / CALIBRATION_PASSES);
	Serial.println(gyro_sum.y / CALIBRATION_PASSES);
	Serial.println(gyro_sum.z / CALIBRATION_PASSES);
}


void mpu_calibrateAccel(int device_adr, axis_int16_t *offset) {
	axis_int16_t accel_raw;
	axis_float_t accel_sum;
	
	
	for(int i = 0; i < CALIBRATION_PASSES; i++) {
		mpu_readAccel(device_adr, &accel_raw);
		accel_sum.x += accel_raw.x;
		accel_sum.y += accel_raw.y;
		accel_sum.z += accel_raw.z;
	}

	offset->x = (int16_t)accel_sum.x / CALIBRATION_PASSES;
	offset->y = (int16_t)accel_sum.y / CALIBRATION_PASSES;
	offset->z = (int16_t)(accel_sum.z / CALIBRATION_PASSES) - ACCEL_2G_SENS;	
	
	Serial.println("Accel-Calibration finished.");
	Serial.println(accel_sum.x / CALIBRATION_PASSES);
	Serial.println(accel_sum.y / CALIBRATION_PASSES);
	Serial.println((accel_sum.z / CALIBRATION_PASSES) - ACCEL_2G_SENS);
}