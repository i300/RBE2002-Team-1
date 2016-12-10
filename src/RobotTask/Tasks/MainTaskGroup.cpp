#include "MainTaskGroup.hpp"

#include "FollowWallTask.hpp"
#include "DriveToCandleTask.hpp"

MainTaskGroup::MainTaskGroup(DriveTrain *driveTrain, FanTurret *turret) : RobotTaskGroup() {
  add(new FollowWallTask(driveTrain, turret));
  add(new DriveToCandleTask(driveTrain, turret));
}
