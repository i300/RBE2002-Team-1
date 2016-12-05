#include "Arduino.h"
#include <Servo.h>
#include "../Motor.hpp"
#include "../../Utilities.h"

#ifndef POLOLU_MOTOR_H
#define POLOLU_MOTOR_H

class PololuMotor : public Motor {
  uint8 pinForward, pinReverse;

  bool16 inverted;

protected:
    int speedToMotorValue(float speed);

public:
    PololuMotor(uint8 pinf, uint8 pinr);
    PololuMotor(uint8 pinf, uint8 pinr, bool16 inverted);
    
    void write(float speed);
};

#endif
