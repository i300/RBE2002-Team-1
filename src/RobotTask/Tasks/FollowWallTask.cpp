#include "FollowWallTask.hpp"

FollowWallTask::FollowWallTask(DriveTrain *driveTrain,
                                 FanTurret *turret) : super(FOLLOW_WALL) {
  _driveTrain = driveTrain;
  _turret = turret;

  timeLastStateSwitch = millis();

  state = FW_FollowWall;
}

/* isFinished - bool8
 * returns true when the task is finished
 */
bool8 FollowWallTask::isFinished() {
  return (state == FW_SeenCandleBase);
}

/* update - void
 * Updates the task
 */
void FollowWallTask::update() {
  super::update();

  unsigned long currentTime = millis();

  if (_turret->canSeeCandle()) {
    state = FW_SeenCandleBase;
  } else {
    _turret->sweep();
  }

  switch (state) {
    case FW_FollowWall: {
      float sideDistance = _driveTrain->getIRReading(IR_SIDE);
      float frontDistance = _driveTrain->getIRReading(IR_FRONT);

      float forwardSpeed = 0.5;
      if (frontDistance < 12) {
        forwardSpeed = 0.25;
      }

      if (sideDistance < 4) {
          _driveTrain->arcadeDrive(forwardSpeed, 0.1);
      } else if (sideDistance > 7) {
          _driveTrain->arcadeDrive(forwardSpeed, -0.1);
      } else {
          _driveTrain->driveStraight(forwardSpeed);
      }

      if (sideDistance > 20) {
        _driveTrain->stop();
        timeLastStateSwitch = currentTime;
        state = FW_SeenGap;
      }

      if (frontDistance < 8) {
        timeLastStateSwitch = currentTime;
        _driveTrain->resetIMU();
        state = FW_Turn90;
      }
      break;
    }

    case FW_Turn90:
      if (_driveTrain->turnDegrees(90)) {
        timeLastStateSwitch = currentTime;
        state = FW_FollowWall;
        _driveTrain->stop();
        _driveTrain->resetIMU();
      }
      break;

    case FW_SeenGap:
      if (_driveTrain->driveEncoderCounts(8, 0.4)) {
        timeLastStateSwitch = currentTime;
        _driveTrain->resetIMU();
        state = FW_TurnAroundWall;
      }
      break;

    case FW_TurnAroundWall:
      if (_driveTrain->turnDegrees(-95)) {
        timeLastStateSwitch = currentTime;
        state = FW_DriveThroughGap;
        _driveTrain->stop();
        _driveTrain->resetIMU();
      }
      break;

    case FW_DriveThroughGap:
      if (_driveTrain->driveEncoderCounts(28, 0.4)) {
        timeLastStateSwitch = currentTime;
        state = FW_TurnTowardWall;
        _driveTrain->resetIMU();
      }
      break;

    case FW_TurnTowardWall:
      if (_driveTrain->turnDegrees(-98)) {
        timeLastStateSwitch = currentTime;
        state = FW_ReFindWall;
        _driveTrain->stop();
        _driveTrain->resetIMU();
      }
      break;

    case FW_ReFindWall:
      if (_driveTrain->driveEncoderCounts(16, 0.4)) {
        timeLastStateSwitch = currentTime;
        state = FW_FollowWall;
      }
      break;

    case FW_SeenCandleBase:
      _driveTrain->stop();
      break;

  }
}

/* getState - int
 * Returns the current state. Used for debugging.
 */
int FollowWallTask::getState() {
  return state;
}

/* finished - void
 * Called once the task is finished. Cleans up the finished task
 */
void FollowWallTask::finished() {

}
