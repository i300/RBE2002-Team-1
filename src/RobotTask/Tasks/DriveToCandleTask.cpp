#include "DriveToCandleTask.hpp"

#include "SubTasks/DriveForwardDistanceTask.hpp"
#include "SubTasks/TurnDegreesTask.hpp"
//#include "SubTasks/DriveForwardToIRDistanceTask.hpp"

DriveToCandleTask::DriveToCandleTask(DriveTrain *driveTrain, FanTurret *turret) : RobotTaskGroup() {
  add(new DriveForwardDistanceTask(driveTrain, 3));
  add(new TurnDegreesTask(driveTrain, 90));
  //add(new DriveForwardToIRDistanceTask(driveTrain, 7));
}
