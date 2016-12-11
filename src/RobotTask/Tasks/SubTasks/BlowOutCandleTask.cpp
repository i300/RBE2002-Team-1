#include "BlowOutCandleTask.hpp"

BlowOutCandleTask::BlowOutCandleTask(DriveTrain *driveTrain, FanTurret *turret) : super(TASK_UNDEFINED) {
  _driveTrain = driveTrain;
  _turret = turret;

  currentAngle = 0;
}

/* isFinished - bool8
 * returns true when the task is finished
 */
bool8 BlowOutCandleTask::isFinished() {
  // TODO: Implement
  return false;
}

/* update - void
 * Updates the task
 */
void BlowOutCandleTask::update() {
  super::update();

  _driveTrain->stop();

  if (currentAngle >= NUM_ANGLES) {
    float sumAngles = 0;
    float momentY = 0;
    for (int i = 0; i < NUM_ANGLES; i++) {
      sumAngles += candleValues[i];
      momentY += (float)i * (float)candleValues[i];
    }
    //Serial.println("A: " + String(sumAngles));
    //Serial.println("M: " + String(momentY));

    float centroid = momentY / sumAngles;
    _turret->setAngle(centroid);
    _turret->fanOn();

  } else {
    _turret->setAngle(currentAngle);
    delay(50);
    candleValues[currentAngle] = _turret->getCandleValue();

    Serial.println(candleValues[currentAngle]);

    currentAngle++;
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
  Serial.println("Finished BlowOutCandleTask");
  _driveTrain->stop();
}
