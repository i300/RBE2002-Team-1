#include <Arduino.h>
#include <Servo.h>
#include "../../Utilities.h"

#ifndef FANTURRET_H
#define FANTURRET_H

class FanTurret {
  Servo fanServo;
  float servoAngle;
  unsigned long lastSweepUpdateTime = 0;
  bool sweepUp = true;
  int sweepTime = 0;

  uint8 fanPin;
  uint8 candleSensorPin;

public:
  FanTurret(uint8 pinServo, uint8 pinFan, uint8 candlePin);

  void setAngle(float angle);
  void changeAngle(float dAngle);
  void sweep();

  int getCandleValue();

  bool canSeeCandle();
  bool pointingAtCandle();

  void fanOn();
  void fanOff();

};

#endif
