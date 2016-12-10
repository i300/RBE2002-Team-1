#include "TurnDegreesTask.hpp"

TurnDegreesTask::TurnDegreesTask(DriveTrain *driveTrain, float degrees) : super(TASK_UNDEFINED) {
  _driveTrain = driveTrain;
  _degrees = degrees;

  _driveTrain->resetIMU();
}

/* isFinished - bool8
 * returns true when the task is finished
 */
bool8 TurnDegreesTask::isFinished() {
  return _driveTrain->turnDegrees(_degrees);
}

/* update - void
 * Updates the task
 */
void TurnDegreesTask::update() {
  super::update();
}

/* finished - void
 * Called once the task is finished. Cleans up the finished task
 */
void TurnDegreesTask::finished() {

}
