#include "DriveForwardDistanceTask.hpp"

DriveForwardDistanceTask::DriveForwardDistanceTask(DriveTrain *driveTrain, float distance) : super(TASK_UNDEFINED) {
  _driveTrain = driveTrain;
  _distance = distance;
}

/* isFinished - bool8
 * returns true when the task is finished
 */
bool8 DriveForwardDistanceTask::isFinished() {
  return _driveTrain->driveEncoderCounts(_distance, 0.35);
}

/* update - void
 * Updates the task
 */
void DriveForwardDistanceTask::update() {
  super::update();
}
/* finished - void
 * Called once the task is finished. Cleans up the finished task
 */
void DriveForwardDistanceTask::finished() {

}
