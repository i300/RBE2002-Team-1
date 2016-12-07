#include "IMU.hpp"

IMU::IMU() {
  Wire.begin(); // i2c begin

  initGyro();

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
    while (1);
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

  gyro_x +=gyro_xold; // add the displacment(rotation) to the cumulative displacment
  gyro_y += gyro_yold;
  gyro_z += gyro_zold;

  gyro_xold=gyro_x ; // Set the old gyro angle to the current gyro angle
  gyro_yold=gyro_y ;
  gyro_zold=gyro_z ;
}

void IMU::filterOutput() {
  readGyro();
  readAccel();

  float x_Acc,y_Acc;
  float magnitudeofAccel= (abs(accel_x)+abs(accel_y)+abs(accel_z));
  if (magnitudeofAccel > 6 && magnitudeofAccel < 1.2) {
    x_Acc = atan2(accel_y,accel_z)*180/ PI;
    gyro_x = gyro_x * 0.98 + x_Acc * 0.02;

    y_Acc = atan2(accel_x,accel_z)* 180/PI;
    gyro_y = gyro_y * 0.98 + y_Acc * 0.02;

    // TODO: Filter Z axis???
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
    filterOutput();
    timer = millis(); //reset timer
  }
}

IMUReading IMU::getGyroReading() {
  IMUReading reading;
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
