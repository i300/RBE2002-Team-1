#include "FanTurret.hpp"

FanTurret::FanTurret(uint8 pinServo, uint8 pinFan) {
  fanServo.attach(pinServo, 1000, 2000);

  fanPin = pinFan;

  pinMode(fanPin, OUTPUT);
  fanOff();
}

void FanTurret::setAngle(int angle) {
  fanServo.write(angle);
}

void FanTurret::fanOn() {
  digitalWrite(fanPin, HIGH);
}

void FanTurret::fanOff() {
  digitalWrite(fanPin, LOW);
}
