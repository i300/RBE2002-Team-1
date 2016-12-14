#include "MainTaskGroup.hpp"

#include "FollowWallTask.hpp"
#include "DriveToCandleTask.hpp"

MainTaskGroup::MainTaskGroup(DriveTrain *driveTrain, FanTurret *turret) : RobotTaskGroup() {
  _driveTrain = driveTrain;
  _turret = turret;

  add(new FollowWallTask(driveTrain, turret, false));
  add(new DriveToCandleTask(driveTrain, turret));
  add(new FollowWallTask(driveTrain, turret, true));
}

void MainTaskGroup::finished() {
  _driveTrain->stop();
}
