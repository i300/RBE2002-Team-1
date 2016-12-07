#include <Arduino.h>
#include <SharpIR.h>
#include "../../EncoderCounter/EncoderCounter.hpp"
#include "../../Motor/Motor.hpp"
#include "../../Utilities.h"

#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

struct EncoderCounts {
  long left;
  long right;
};

enum IRLocation {
  IR_FRONT,
  IR_SIDE,
  IR_REAR
};

class DriveTrain {
  Motor *_leftMotor, *_rightMotor;
  EncoderCounter *_encoders;

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

  void writeToMotors(float left, float right);

public:
  DriveTrain(Motor *leftMotor, Motor *rightMotor, EncoderCounter *encoderCounter,
             uint8 frontIRPin, uint8 sideIRPin, uint8 rearIRPin);
  void arcadeDrive(float speed, float rotation);
  void tankDrive(float left, float right);

  void resetEncoderCount();
  EncoderCounts getEncoderCount();

  float getIRReading(IRLocation loc);

  void update();
  void stop();
};

#endif
