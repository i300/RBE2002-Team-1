#include "Arduino.h"
#include "../Utilities.h"

#include <Wire.h>

#include <L3G.h>
#include <LSM303.h>

#ifndef IMU_H
#define IMU_H

typedef struct {
  float x;
  float y;
  float z;
} IMUReading;

class IMU {
  L3G gyro;
  LSM303 accel;

  float G_Dt=0.020;    // Integration time (DCM algorithm)  We will run the integration loop at 50Hz if possible

  long timer=0; // integration timer

  float G_gain = 0.00875; // gyros gain factor for 250deg/sec
  float gyro_x = 0; // gyro x val
  float gyro_y = 0; // gyro x val
  float gyro_z = 0; // gyro x val
  float gyro_xold = 0; // gyro cummulative x value
  float gyro_yold = 0; // gyro cummulative y value
  float gyro_zold = 0; // gyro cummulative z value
  float gerrx = 0; // gyro x error
  float gerry = 0; // gyro y error
  float gerrz = 0; // gyro z error

  float A_gain = 0.00875; // accel gain factor (for 250deg/sec ??)
  float accel_x = 0; // accel x val
  float accel_y = 0; // accel x val
  float accel_z = 0; // accel x val
  float accel_xold = 0; // accel cummulative x value
  float accel_yold = 0; // accel cummulative y value
  float accel_zold = 0; // accel cummulative z value
  float aerrx = 0; // Accel x error
  float aerry = 0; // Accel y error
  float aerrz = 0; // Accel z error

protected:
  void initAccel();
  void initGyro();

  void gyroZero();

  void readGyro();
  void readAccel();

  void filterOutput();


public:
  IMU();
  void init();
  IMUReading getGyroReading();
  IMUReading getAccelReading();
  void clear();
  void update();
};

#endif
