#include "MainTaskGroup.hpp"

#include "FollowWallTask.hpp"
#include "DriveToCandleTask.hpp"

#include "SubTasks/DriveForwardDistanceTask.hpp"
#include "SubTasks/TurnDegreesTask.hpp"

MainTaskGroup::MainTaskGroup(DriveTrain *driveTrain, FanTurret *turret) : RobotTaskGroup() {
  _driveTrain = driveTrain;
  _turret = turret;

  add(new FollowWallTask(driveTrain, turret));
  add(new DriveToCandleTask(driveTrain, turret));
  //add(new DriveForwardDistanceTask(driveTrain, 12, 0.35));
}

void MainTaskGroup::finished() {
  _driveTrain->stop();
}
