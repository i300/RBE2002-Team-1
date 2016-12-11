#include "IMU.hpp"

IMU::IMU() {

}

void IMU::init() {
  Serial.println("Wire Begin");
  Wire.begin(); // i2c begin

  Serial.println("Gyro Init");
  initGyro();

  Serial.println("Gyro Enable");
  timer = millis(); // init timer for first reading
  gyro.enableDefault(); // gyro init. default 250/deg/s
  delay(1000);// allow time for gyro to settle

  Serial.println("starting gyro calibration");
  gyroZero();
  initAccel();
}

void IMU::initAccel() {
  accel.init();
  accel.enableDefault();
  Serial.print("Accel Device ID");
  Serial.println(accel.getDeviceType());
  switch (accel.getDeviceType()) {
    case LSM303::device_D:
      accel.writeReg(LSM303::CTRL2, 0x18); // 8 g full scale: AFS = 011
      break;
    case LSM303::device_DLHC:
      accel.writeReg(LSM303::CTRL_REG4_A, 0x28); // 8 g full scale: FS = 10; high resolution output mode
      break;
    default: // DLM, DLH
      accel.writeReg(LSM303::CTRL_REG4_A, 0x30); // 8 g full scale: FS = 11
  }
}

void IMU::initGyro() {
  if (!gyro.init()) {
    Serial.println("Failed to autodetect gyro type!");
    while (1) {
      delay(1000);
    }
  }
}

void IMU::gyroZero() {
  for(int i =0;i<200;i++){
    gyro.read();
    gerrx+=gyro.g.x;
    gerry+=gyro.g.y;
    gerrz+=gyro.g.z;
    delay(20);
  }

  // average reading to obtain an error/offset
  gerrx = gerrx/200;
  gerry = gerry/200;
  gerrz = gerrz/200;
}

void IMU::readGyro() {
  gyro.read(); // read gyro
  gyro_x=(float)(gyro.g.x-gerrx)*G_gain; // offset by error then multiply by gyro gain factor
  gyro_y=(float)(gyro.g.y-gerry)*G_gain;
  gyro_z=(float)(gyro.g.z-gerrz)*G_gain;

  gyro_x = gyro_x*G_Dt; // Multiply the angular rate by the time interval
  gyro_y = gyro_y*G_Dt;
  gyro_z = gyro_z*G_Dt;

  gyro_x += gyro_xold; // add the displacment(rotation) to the cumulative displacment
  gyro_y += gyro_yold;
  gyro_z += gyro_zold;

  gyro_xold=gyro_x ; // Set the old gyro angle to the current gyro angle
  gyro_yold=gyro_y ;
  gyro_zold=gyro_z ;
}

void IMU::filterOutput() {
  readGyro();
  readAccel();

  float x_Acc,y_Acc,z_Acc;
  float magnitudeofAccel= (abs(accel_x)+abs(accel_y)+abs(accel_z));
  if (magnitudeofAccel > 6 && magnitudeofAccel < 1.2) {
    x_Acc = atan2(accel_y,accel_z)*180/ PI;
    gyro_x = gyro_x * 0.98 + x_Acc * 0.02;

    y_Acc = atan2(accel_x,accel_z)* 180/PI;
    gyro_y = gyro_y * 0.98 + y_Acc * 0.02;

    z_Acc = atan2(accel_x,accel_y)* 180/PI;
    gyro_z = gyro_z * 0.98 + z_Acc * 0.02;
  }
}

void IMU::readAccel() {
  accel.readAcc();

  accel_x = accel.a.x >> 4; // shift left 4 bits to use 12-bit representation (1 g = 256)
  accel_y = accel.a.y >> 4;
  accel_z = accel.a.z >> 4;

  // accelerations in G
  accel_x = (accel_x/256);
  accel_y = (accel_y/256);
  accel_z = (accel_z/256);
}

void IMU::update() {
  // 50hz update loop
  if ((millis() - timer) >= 20) {
    //filterOutput();
    readGyro();
    timer = millis(); //reset timer
  }
}

void IMU::clear() {
  gyro_x = 0; // gyro x val
  gyro_y = 0; // gyro x val
  gyro_z = 0; // gyro x val
  gyro_xold = 0; // gyro cummulative x value
  gyro_yold = 0; // gyro cummulative y value
  gyro_zold = 0; // gyro cummulative z value
  gerrx = 0; // gyro x error
  gerry = 0; // gyro y error
  gerrz = 0; // gyro z error

  accel_x = 0; // accel x val
  accel_y = 0; // accel x val
  accel_z = 0; // accel x val
  accel_xold = 0; // accel cummulative x value
  accel_yold = 0; // accel cummulative y value
  accel_zold = 0; // accel cummulative z value
  aerrx = 0; // Accel x error
  aerry = 0; // Accel y error
  aerrz = 0; // Accel z error
}

IMUReading IMU::getGyroReading() {
  IMUReading reading = {0};
  reading.x = gyro_x;
  reading.y = gyro_y;
  reading.z = gyro_z;
  return reading;
}

IMUReading IMU::getAccelReading() {
  IMUReading reading = {0};
  reading.x = accel_x;
  reading.y = accel_y;
  reading.z = accel_z;
  return reading;
}
