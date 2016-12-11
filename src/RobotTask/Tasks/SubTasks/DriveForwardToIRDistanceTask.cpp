#include "DriveForwardToIRDistanceTask.hpp"

DriveForwardToIRDistanceTask::DriveForwardToIRDistanceTask(DriveTrain *driveTrain, float distance) : super(TASK_UNDEFINED) {
  _driveTrain = driveTrain;
  _distance = distance;
}

/* isFinished - bool8
 * returns true when the task is finished
 */
bool8 DriveForwardToIRDistanceTask::isFinished() {
  return _driveTrain->getIRReading(IR_FRONT) < _distance;
}

/* update - void
 * Updates the task
 */
void DriveForwardToIRDistanceTask::update() {
  super::update();

  _driveTrain->driveStraight(0.35);
}

/* init - void
 * Called on the first update of the task to setup anything thats necessary
 */
void DriveForwardToIRDistanceTask::init() {
  Serial.println("Init DriveForwardToIRDistanceTask");
  _driveTrain->resetIMU();
}


/* finished - void
 * Called once the task is finished. Cleans up the finished task
 */
void DriveForwardToIRDistanceTask::finished() {
  Serial.println("Finished DriveForwardToIRDistanceTask");
  _driveTrain->stop();
}
