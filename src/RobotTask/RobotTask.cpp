#include "RobotTask.hpp"

/* constructor -
 */
RobotTask::RobotTask() {
  _type = TASK_UNDEFINED;
  _timeStarted = millis();

  _finished = false;
  _initialized = false;
}

/* constructor -
 * type - the task type
 */
RobotTask::RobotTask(RobotTaskType type) {
  _type = type;
  _timeStarted = millis();

  _finished = false;
  _initialized = false;
}

/* getTimeStarted - unsigned long timeStarted
 * Returns the millis() when the task was started.
 */
unsigned long RobotTask::getTimeStarted() {
  return _timeStarted;
}

/* getType - RobotTaskType type
 * Returns the type of the task
 */
RobotTaskType RobotTask::getType() {
  return _type;
}

/* isFinished - bool8 finished
 * Returns true if the task is finished.
 */
bool8 RobotTask::isFinished() {
  return true;
}

/* update - void
 * Updates the robot based on the current task. When the task is finished,
 * calls finished() once.
 */
void RobotTask::update() {
  if (!_initialized) {
    init();
    _initialized = true;
  }

  if (isFinished() && !_finished) {
    finished();
    _finished = true;
  }
}

/* getState - int currentState
 * Returns the current state.
 */
int RobotTask::getState() {
  return 0;
}
