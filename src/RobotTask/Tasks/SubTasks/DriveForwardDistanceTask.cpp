#include "DriveForwardDistanceTask.hpp"

DriveForwardDistanceTask::DriveForwardDistanceTask(DriveTrain *driveTrain, float distance) : super(TASK_UNDEFINED) {
  _driveTrain = driveTrain;
  _distance = distance;
}

/* isFinished - bool8
 * returns true when the task is finished
 */
bool8 DriveForwardDistanceTask::isFinished() {
  EncoderCounts e = _driveTrain->getEncoderCount();
  float dist = (e.left + e.right) / 2.0;
  float initialD = (initialE.left + initialE.right) / 2.0;
  return (dist - initialD) >= _distance;
}

/* update - void
 * Updates the task
 */
void DriveForwardDistanceTask::update() {
  super::update();

  _driveTrain->driveStraight(0.35);
}

void DriveForwardDistanceTask::init() {
  Serial.println("Init DriveForwardDistanceTask");
  _driveTrain->resetIMU();
  initialE = _driveTrain->getEncoderCount();
}

/* finished - void
 * Called once the task is finished. Cleans up the finished task
 */
void DriveForwardDistanceTask::finished() {
  Serial.println("Finished DriveForwardDistanceTask");
  _driveTrain->stop();
}
