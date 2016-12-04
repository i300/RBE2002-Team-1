#include <Arduino.h>
#include <LiquidCrystal.h>
#include "../../Motor/Motor.hpp"
#include "../../Utilities.h"

#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

class DriveTrain {
  Motor *_leftMotor, *_rightMotor;
  LiquidCrystal *_lcd;

  void writeToMotors(float left, float right);

public:
  DriveTrain(Motor *leftMotor, Motor *rightMotor);
  void arcadeDrive(float speed, float rotation);
  void tankDrive(float left, float right);

  void stop();
};

#endif
