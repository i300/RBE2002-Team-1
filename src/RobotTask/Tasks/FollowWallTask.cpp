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

  switch (state) {
    case FW_FollowWall: {
      float error = WALL_DISTANCE - _driveTrain->getIRReading(IR_SIDE);
      _driveTrain->arcadeDrive(0.5, error * kP_wallfollow);
      break;
    }

    case FW_Turn90:
      break;

    case FW_SeenGap:
      break;

    case FW_TurnAroundWall:
      break;

    case FW_SeenCandleBase:
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
