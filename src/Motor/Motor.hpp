#include "Arduino.h"
#include "../Utilities.h"

#ifndef MOTOR_H
#define MOTOR_H

class Motor {
protected:
  virtual int speedToMotorValue(float speed);

public:
  Motor() {}
  virtual void write(float speed) {}
};

#endif
