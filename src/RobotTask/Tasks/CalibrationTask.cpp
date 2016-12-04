#include "CalibrationTask.hpp"

CalibrationTask::CalibrationTask(DriveTrain *driveTrain) {
  _driveTrain = driveTrain;

  timeLastStateSwitch = millis();

  state = CS_FINISHED; //TODO: Change this
}

/* isFinished - bool8
 * returns true when the task is finished
 */
bool8 CalibrationTask::isFinished() {
  return (state == CS_FINISHED) && (millis() > timeLastStateSwitch + 500);
}

/* update - void
 * Updates the task
 */
void CalibrationTask::update() {
  super::update();

  unsigned long currentTime = millis();

  switch (state) {
    case CS_FINISHED:
      break;

  }
}

/* getState - int
 * Returns the current state. Used for debugging.
 */
int CalibrationTask::getState() {
  return state;
}

/* finished - void
 * Called once the task is finished. Cleans up the finished task
 */
void CalibrationTask::finished() {

}
