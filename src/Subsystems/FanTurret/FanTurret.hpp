#include <Arduino.h>
#include <Servo.h>
#include "../../Utilities.h"

#ifndef FANTURRET_H
#define FANTURRET_H

class FanTurret {
  Servo fanServo;
  int servoAngle;

  uint8 fanPin;

public:
  FanTurret(uint8 pinServo, uint8 pinFan);

  void setAngle(int angle);
  void changeAngle(int dAngle);
  void sweepServo();

  void fanOn();
  void fanOff();

};

#endif
