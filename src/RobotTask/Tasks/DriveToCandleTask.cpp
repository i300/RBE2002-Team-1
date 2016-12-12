#include "DriveToCandleTask.hpp"

#include "SubTasks/DriveForwardDistanceTask.hpp"
#include "SubTasks/TurnDegreesTask.hpp"
#include "SubTasks/DriveForwardToIRDistanceTask.hpp"
#include "SubTasks/BlowOutCandleTask.hpp"

DriveToCandleTask::DriveToCandleTask(DriveTrain *driveTrain, FanTurret *turret) : RobotTaskGroup() {
  add(new DriveForwardDistanceTask(driveTrain, -1, -0.35));
  add(new TurnDegreesTask(driveTrain, 90));
  add(new DriveForwardToIRDistanceTask(driveTrain, 4));
  add(new DriveForwardDistanceTask(driveTrain, 1, 0.2));
  add(new TurnDegreesTask(driveTrain, -90));
  add(new BlowOutCandleTask(driveTrain, turret));
}
