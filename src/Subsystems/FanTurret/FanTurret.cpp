#include "FanTurret.hpp"

FanTurret::FanTurret(uint8 pinServo, uint8 pinFan, uint8 candlePin, uint8 candleFoundPin, uint8 candleOutPin) {
  fanServo.attach(pinServo);

  _candleFoundPin = candleFoundPin;
  _candleOutPin = candleOutPin;

  fanPin = pinFan;
  candleSensorPin = candlePin;
  servoAngle = 0;
  setAngle(0);

  pinMode(fanPin, OUTPUT);
  pinMode(candleOutPin, OUTPUT);
  pinMode(candleFoundPin, OUTPUT);
  digitalWrite(candleOutPin, LOW);
  digitalWrite(candleFoundPin, LOW);
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

void FanTurret::setCandleFound() {
  digitalWrite(_candleFoundPin, HIGH);
}

void FanTurret::setCandleOut() {
  digitalWrite(_candleOutPin, HIGH);
}
