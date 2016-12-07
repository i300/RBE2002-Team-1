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
  float gyro_x; // gyro x val
  float gyro_y; // gyro x val
  float gyro_z; // gyro x val
  float gyro_xold; // gyro cummulative x value
  float gyro_yold; // gyro cummulative y value
  float gyro_zold; // gyro cummulative z value
  float gerrx; // gyro x error
  float gerry; // gyro y error
  float gerrz; // gyro z error

  float A_gain = 0.00875; // accel gain factor (for 250deg/sec ??)
  float accel_x; // accel x val
  float accel_y; // accel x val
  float accel_z; // accel x val
  float accel_xold; // accel cummulative x value
  float accel_yold; // accel cummulative y value
  float accel_zold; // accel cummulative z value
  float aerrx; // Accel x error
  float aerry; // Accel y error
  float aerrz; // Accel z error

protected:
  void initAccel();
  void initGyro();

  void gyroZero();

  void readGyro();
  void readAccel();

  void filterOutput();

public:
  IMU();
  IMUReading getGyroReading();
  IMUReading getAccelReading();
  void update();
};

#endif
