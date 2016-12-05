#include "DriveTrain.hpp"

/* constructor
 *
 * leftMotorPin - left motor object
 * rightMotorPin - Right motor object
 * encoderCounter - Encoder Counter object
 */
DriveTrain::DriveTrain(Motor *leftMotor, Motor *rightMotor, EncoderCounter *encoderCounter) {
  _leftMotor = leftMotor;
  _rightMotor = rightMotor;
  _encoders = encoderCounter;
}

/* writeToMotors - void
 *
 * left - Left motor speed
 * right - Light motor speed
 */
void DriveTrain::writeToMotors(float left, float right) {
  _leftMotor->write(left);
  _rightMotor->write(right);
}

/* arcadeDrive - void
 * Drives robot based on a forward speed and rotation value
 *
 * speed - Speed robot will drive at
 * rotation - Value from -1 (left) to 1 (right)
 */
void DriveTrain::arcadeDrive(float speed, float rotation) {
  if (rotation == 0) tankDrive(speed, speed);

  // constrain speed and roation to intended values (-1 to 1)
  speed = constrain(speed, -1, 1);
  rotation = constrain(rotation, -1, 1);

  float leftMotorSpeed, rightMotorSpeed;

  // credit to Joel Gallant
  // https://gist.github.com/joelg236/a294a03a1094167ff49f
  if (speed > 0.0) {
    if (rotation > 0.0) {
      leftMotorSpeed = speed - rotation;
      rightMotorSpeed = max(speed, rotation);
    } else {
      leftMotorSpeed = max(speed, -rotation);
      rightMotorSpeed = speed + rotation;
    }
  } else {
    if (rotation > 0.0) {
      leftMotorSpeed = -max(-speed, rotation);
      rightMotorSpeed = speed + rotation;
    } else {
      leftMotorSpeed = speed - rotation;
      rightMotorSpeed = -max(-speed, -rotation);
    }
  }

  // drive robot
  writeToMotors(leftMotorSpeed, rightMotorSpeed);
}

/* tankDrive - void
 * Drive robot based on left values and right speeds
 *
 * left - Left speed
 * right - Right speed
 */
void DriveTrain::tankDrive(float left, float right) {
  // constrain speeds to intended values (-1 to 1)
  left = constrain(left, -1, 1);
  right = constrain(right, -1, 1);

  // write to motors
  writeToMotors(left, right);
}

/* stop - void
 * Sends zero to the drive motors to stop motion
 */
void DriveTrain::stop() {
  writeToMotors(0, 0);
}
