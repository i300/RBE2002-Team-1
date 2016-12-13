#include "FanTurret.hpp"

FanTurret::FanTurret(uint8 pinServo, uint8 pinFan, uint8 candlePin) {
  fanServo.attach(pinServo);

  fanPin = pinFan;
  candleSensorPin = candlePin;
  servoAngle = 0;
  setAngle(0);

  pinMode(fanPin, OUTPUT);
  fanOff();
}

void FanTurret::setAngle(float angle) {
  servoAngle = angle;
  fanServo.write(angle);
}

void FanTurret::changeAngle(float dAngle) {
  setAngle(servoAngle + dAngle);
}

void FanTurret::sweep() {
  unsigned long currentTime = millis();

  if (currentTime > lastSweepUpdateTime + 1000) {
    lastSweepUpdateTime = currentTime;
  }

  unsigned long dt = currentTime - lastSweepUpdateTime; // dt in milliseconds

  float dAngle = dt * (180.0  / 400.0); // dt * (180 deg / 400 ms)

  if (servoAngle >= 180) {
    sweepUp = false;
  } if (servoAngle <= 0) {
    sweepUp = true;
  }

  lastSweepUpdateTime = currentTime;

  changeAngle(sweepUp ? dAngle : -dAngle);
}

int FanTurret::getCandleValue() {
  return analogRead(candleSensorPin);
}

bool FanTurret::canSeeCandle() {
  return (getCandleValue() < 700);
}

bool FanTurret::pointingAtCandle() {
  return (getCandleValue() < 250);
}

void FanTurret::fanOn() {
  digitalWrite(fanPin, HIGH);
}

void FanTurret::fanOff() {
  digitalWrite(fanPin, LOW);
}
