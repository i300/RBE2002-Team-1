#include "VexMotor.hpp"

/* constructor
 *
 * pin - Pin to attach the motor to
 */
VexMotor::VexMotor(int8 pin) {
  motor.attach(pin, 1000, 2000);
  inverted = false;
}

/* constructor
 *
 * pin - Pin to attach the motor to
 * invert - sets motor to be inverted or not
 */
VexMotor::VexMotor(int8 pin, bool16 invert) {
  motor.attach(pin, 1000, 2000);
  inverted = invert;
}

/* speedToMotorValue - Converts a speed into a motor value
 *
 * speed - Speed (-1 to 1)
 */
int VexMotor::speedToMotorValue(float speed) {
  int integerSpeed = speed * 100;
  return (int)map(integerSpeed, -100, 100, MOTOR_MIN_VALUE, MOTOR_MAX_VALUE);
}

/* write - Converts a speed to a motor value, then writes it to the motor
 *
 * speed - Speed (-1 to 1)
 */
void VexMotor::write(float speed) {
  int motorValue = speedToMotorValue(speed);

  motor.write(inverted ? MOTOR_MAX_VALUE - motorValue : motorValue);
}
