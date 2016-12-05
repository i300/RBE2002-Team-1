#include <Arduino.h>
#include <LiquidCrystal.h>
#include "../../EncoderCounter/EncoderCounter.hpp"
#include "../../Motor/Motor.hpp"
#include "../../Utilities.h"

#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

class DriveTrain {
  Motor *_leftMotor, *_rightMotor;
  EncoderCounter *_encoders;
  LiquidCrystal *_lcd;

  void writeToMotors(float left, float right);

public:
  DriveTrain(Motor *leftMotor, Motor *rightMotor, EncoderCounter *encoderCounter);
  void arcadeDrive(float speed, float rotation);
  void tankDrive(float left, float right);

  void stop();
};

#endif
