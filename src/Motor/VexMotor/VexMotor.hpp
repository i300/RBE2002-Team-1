#include "Arduino.h"
#include <Servo.h>
#include "../Motor.hpp"
#include "../../Utilities.h"

#ifndef VEX_MOTOR_H
#define VEX_MOTOR_H

class VexMotor : public Motor {
  Servo motor;

  bool16 inverted;

  static const int MOTOR_MAX_VALUE = 180;
  static const int MOTOR_MIN_VALUE = 0;

protected:
    int speedToMotorValue(float speed);

public:
    VexMotor(int8 pin);
    VexMotor(int8 pin, bool16 inverted);
    void write(float speed);
};

#endif
