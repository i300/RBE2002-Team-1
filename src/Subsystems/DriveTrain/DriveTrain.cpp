#include "DriveTrain.hpp"

/* constructor
 *
 * leftMotorPin - left motor object
 * rightMotorPin - Right motor object
 * encoderCounter - Encoder Counter object
 */
 DriveTrain::DriveTrain(Motor *leftMotor, Motor *rightMotor, EncoderCounter *encoderCounter, IMU *imu,
                        uint8 frontIRPin, uint8 sideIRPin, uint8 rearIRPin) {
  _leftMotor = leftMotor;
  _rightMotor = rightMotor;
  _encoders = encoderCounter;
  _imu = imu;

  frontIR = new SharpIR(frontIRPin, 1080);
  sideIR = new SharpIR(sideIRPin, 1080);
  rearIR = new SharpIR(rearIRPin, 1080);

  writeToMotors(0, 0);
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
  speed = constrain(speed, -1.0, 1.0);
  rotation = constrain(rotation, -1.0, 1.0);

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
  leftSetpoint = leftMotorSpeed;
  rightSetpoint = rightMotorSpeed;
}

void DriveTrain::driveStraight(float speed) {
  unsigned long currentDriveTime = millis();

  if (currentDriveTime > lastDriveUpdate + 1000) {
    sumDriveError = 0;
    lastDriveError = 0;
  }

  IMUReading angle = _imu->getGyroReading();
  float error = 0 - angle.z;

  float iPart = sumDriveError;
  float dPart = error - lastDriveError;

  sumDriveError += error;
  lastDriveError = error;

  float pidOutput = (error * kP_driving) + (iPart * kI_driving) + (dPart * kD_driving);
  pidOutput = constrain(pidOutput, -1, 1);

  arcadeDrive(speed, pidOutput);

  lastDriveUpdate = currentDriveTime;
}

bool DriveTrain::driveEncoderCounts(float targetDistance, float maxSpeed) {
  unsigned long currentTime = millis();
  EncoderCounts e = getEncoderCount();

  if (currentTime > lastEncoderDriveUpdate + 1000) {
    logLeftEncoder = e.left;
    logRightEncoder = e.right;
  }

  float currentDistance = (e.left + e.right) / 2.0;

  targetDistance += (logLeftEncoder + logRightEncoder) / 2.0;

  float error = targetDistance - currentDistance;

  error = constrain(error, -1, 1);

  tankDrive(maxSpeed * error * kP_encoder, maxSpeed * error * kP_encoder);

  lastEncoderDriveUpdate = currentTime;

  return (error < encoderTolerance);
}

void DriveTrain::resetIMU() {
  _imu->clear();
}

// Direction: 1 is cw, -1 is ccw
bool DriveTrain::turnDegrees(float deg) {
  unsigned long currentTime = millis();

  if (currentTime > lastTurnUpdate + 1000) {
    sumTurnError = 0;
    lastTurnError = 0;
  }

  IMUReading r = _imu->getGyroReading();
  float error = deg - r.z;

  float iPart = sumTurnError;
  float dPart = error - lastTurnError;

  sumTurnError += error;
  lastTurnError = error;

  float pidOutput = (error * kP_turning) + (iPart * kI_turning) + (dPart * kD_turning);
  pidOutput = constrain(pidOutput, -1, 1);

  Serial.println("TD Er: " + String(error));

  float turnSpeed = 1;

  tankDrive(-turnSpeed * pidOutput, turnSpeed * pidOutput );

  lastTurnUpdate = currentTime;

  return (abs(error) < 10) && (abs(dPart) < 0.1);
}

/* tankDrive - void
 * Drive robot based on left values and right speeds
 *
 * left - Left speed
 * right - Right speed
 */
void DriveTrain::tankDrive(float left, float right) {
  // constrain speeds to intended values (-1 to 1)
  left = constrain(left, -1.0, 1.0);
  right = constrain(right, -1.0, 1.0);

  // write to motors
  leftSetpoint = left;
  rightSetpoint = right;
}

void DriveTrain::resetEncoderCount() {
  _encoders->clearCount();
}

EncoderCounts DriveTrain::getEncoderCount() {
  EncoderCounts e = {0};
  e.left = -_encoders->readEncoder(2) * encoderConstant;
  e.right = _encoders->readEncoder(1) * encoderConstant;
  return e;
}

float DriveTrain::getIRReading(IRLocation loc) {
  switch (loc) {
    case IR_FRONT:
      return frontIR->distance() / 2.54;
      break;

    case IR_SIDE:
      return sideIR->distance() / 2.54;
      break;

    case IR_REAR:
      return rearIR->distance() / 2.54;
      break;
  }

  return 0;
}

void DriveTrain::update() {
  if (ramping) {
    leftSpeed += (leftSetpoint - leftSpeed) * kP_ramping;
    rightSpeed += (rightSetpoint - rightSpeed) * kP_ramping;
  } else {
    leftSpeed = leftSetpoint;
    rightSpeed = rightSetpoint;
  }

  writeToMotors(leftSpeed, rightSpeed);
}

/* stop - void
 * Sends zero to the drive motors to stop motion
 */
void DriveTrain::stop() {
  leftSetpoint = 0;
  rightSetpoint = 0;
  rightSpeed = 0;
  leftSpeed = 0;
}
