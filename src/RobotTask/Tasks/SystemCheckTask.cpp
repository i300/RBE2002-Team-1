#include "SystemCheckTask.hpp"

SystemCheckTask::SystemCheckTask(DriveTrain *driveTrain,
                                 FanTurret *turret) : super(SYSTEM_CHECK) {
  _driveTrain = driveTrain;
  _turret = turret;

  timeLastStateSwitch = millis();

  state = CS_DRIVE1; //TODO: Change this
}

/* isFinished - bool8
 * returns true when the task is finished
 */
bool8 SystemCheckTask::isFinished() {
  return false; //(state == CS_FINISHED) && (millis() > timeLastStateSwitch + 500);
}

/* update - void
 * Updates the task
 */
void SystemCheckTask::update() {
  super::update();

  unsigned long currentTime = millis();

  switch (state) {
    case CS_DRIVE1:
      _turret->setAngle(0);
      _driveTrain->driveStraight(0.5);
      if (_driveTrain->getIRReading(IR_FRONT) < 5) {
        timeLastStateSwitch = currentTime;
        _driveTrain->resetIMU();
        state = CS_TURN1;
      }
      break;

    case CS_TURN1: {
      _turret->setAngle(90);
      if (_driveTrain->turnDegrees(90, 1)) {
        timeLastStateSwitch = currentTime;
        state = CS_DRIVE2;
        _driveTrain->resetIMU();
        _turret->fanOn();
        _turret->setAngle(180);
      }
      break;
    }

    case CS_DRIVE2:
      _driveTrain->driveStraight(0.5);
      if (_driveTrain->getIRReading(IR_FRONT) < 5) {
        timeLastStateSwitch = currentTime;
        state = CS_FINISHED;
        _turret->fanOff();
      }
      break;

    case CS_FINISHED:
      _driveTrain->tankDrive(0, 0);
      break;

  }
}

/* getState - int
 * Returns the current state. Used for debugging.
 */
int SystemCheckTask::getState() {
  return state;
}

/* finished - void
 * Called once the task is finished. Cleans up the finished task
 */
void SystemCheckTask::finished() {

}
