#include <Arduino.h>
#include <SharpIR.h>
#include "../../EncoderCounter/EncoderCounter.hpp"
#include "../../IMU/IMU.hpp"
#include "../../Motor/Motor.hpp"
#include "../../Utilities.h"

#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

struct EncoderCounts {
  float left;
  float right;
};

struct RobotPosition {
  float x;
  float y;
  float theta;
};

enum IRLocation {
  IR_FRONT,
  IR_SIDE,
  IR_REAR
};

class DriveTrain {
  Motor *_leftMotor, *_rightMotor;
  EncoderCounter *_encoders;
  IMU *_imu;

  SharpIR *frontIR;
  SharpIR *rearIR;
  SharpIR *sideIR;

  boolean ramping = true;

  const float kP_ramping = 0.01;
  const float speedTolerance = 0.01;

  float leftSpeed = 0;
  float leftSetpoint = 0;

  float rightSpeed = 0;
  float rightSetpoint = 0;

  // Localization Variables
  EncoderCounts lastE = {0};
  RobotPosition pos = {0};
  unsigned long lastLocalizatonUpdate = 0;

  // turning variables
  float lastTurnError = 0;
  float sumTurnError = 0;
  unsigned long lastTurnUpdate = 0;

  const float kP_turning = 0.0075;
  const float kI_turning = 0.0;
  const float kD_turning = 0.005;

  // driving variables
  float lastDriveError = 0;
  const float encoderConstant = (2.75 * 3.1415926) / 3200.0;
  unsigned long lastDriveUpdate = 0;

  const float kP_driving = 0.02;
  const float kI_driving = 0;
  const float kD_driving = 0;

  // encoder driving variables
  unsigned long lastEncoderDriveUpdate = 0;
  long logLeftEncoder = 0;
  long logRightEncoder = 0;
  float sumDriveError = 0;

  const float kP_encoder = 1;
  const float encoderTolerance = 0.1;

  void writeToMotors(float left, float right);

public:
  DriveTrain(Motor *leftMotor, Motor *rightMotor, EncoderCounter *encoderCounter, IMU* imu,
             uint8 frontIRPin, uint8 sideIRPin, uint8 rearIRPin);
  void arcadeDrive(float speed, float rotation);
  void tankDrive(float left, float right);

  void resetIMU();
  bool turnDegrees(float deg);
  bool driveEncoderCounts(float targetDistance, float maxSpeed);
  void driveStraight(float speed);

  void resetEncoderCount();
  EncoderCounts getEncoderCount();

  float getIRReading(IRLocation loc);

  void localize();
  RobotPosition getRobotPosition();

  void update();
  void stop();
};

#endif
