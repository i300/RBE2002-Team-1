#include "PololuMotor.hpp"

/* constructor
 *
 * pinf - Forward motor pin
 * pinr - Reverse motor pin
 */
PololuMotor::PololuMotor(uint8 pinf, uint8 pinr) {
  pinForward = pinf;
  pinReverse = pinr;
  inverted = false;
}

/* constructor
 *
 * pinf - Forward motor pin
 * pinr - Reverse motor pin
 * invert - sets motor to be inverted or not
 */
PololuMotor::PololuMotor(uint8 pinf, uint8 pinr, bool16 invert) {
  pinForward = pinf;
  pinReverse = pinr;
  inverted = invert;
}

/* speedToMotorValue - Converts a speed into a motor value
 *
 * speed - Speed (-1 to 1)
 */
int PololuMotor::speedToMotorValue(float speed) {
  speed = constrain(speed, -1, 1);

  return speed * 255;
}

/* write - Converts a speed to a motor value, then writes it to the motor
 *
 * speed - Speed (-1 to 1)
 */
void PololuMotor::write(float speed) {
  int motorValue = speedToMotorValue(speed);

  if (motorValue >= 0) {
    analogWrite(pinForward, motorValue);
    analogWrite(pinReverse, 0);
  } else {
    analogWrite(pinForward, 0);
    analogWrite(pinReverse, motorValue);
  }
}
