#include "BlowOutCandleTask.hpp"

BlowOutCandleTask::BlowOutCandleTask(DriveTrain *driveTrain, FanTurret *turret) : super(TASK_UNDEFINED) {
  _driveTrain = driveTrain;
  _turret = turret;

  currentAngle = 0;
  maxBlowTime = 0;
  blowAttempts = 0;
  candleFound = false;
  candleOut = false;
  candleFound = false;
}

/* isFinished - bool8
 * returns true when the task is finished
 */
bool8 BlowOutCandleTask::isFinished() {
  return candleOut;
}

/* update - void
 * Updates the task
 */
void BlowOutCandleTask::update() {
  super::update();

  unsigned long currentTime = millis();

  _driveTrain->stop();

  if (candleOut) return;

  if (candleFound) {

    if (currentTime < maxBlowTime) {
      _turret->fanOn();
    } else {
      _turret->fanOff();
      delay(2500);
      if (!_turret->canSeeCandle()) {
        candleOut = true;
        _turret->setCandleOut();
        _driveTrain->recordPosition();
      } else {
        blowAttempts++;
        maxBlowTime = currentTime + 10000 + (2500 * blowAttempts);
      }
    }

  } else {
    if (currentAngle >= NUM_ANGLES) {
      float sumAngles = 0;
      float momentY = 0;
      for (int i = 0; i < NUM_ANGLES; i++) {
        sumAngles += candleValues[i];
        momentY += (float)i * (float)candleValues[i];
      }

      float centroid = momentY / sumAngles;
      _turret->setAngle(180 - centroid);

      candleFound = true;
      maxBlowTime = currentTime + 10000;
      blowAttempts++;
    } else {
      _turret->setAngle(currentAngle);
      delay(50);
      candleValues[currentAngle] = _turret->getCandleValue();

      Serial.println(candleValues[currentAngle]);

      currentAngle++;
    }
  }
}

/* init - void
 * Called on the first update of the task to setup anything thats necessary
 */
void BlowOutCandleTask::init() {
  Serial.println("Init BlowOutCandleTask");
  _driveTrain->resetIMU();
}


/* finished - void
 * Called once the task is finished. Cleans up the finished task
 */
void BlowOutCandleTask::finished() {
  _driveTrain->stop();
}
