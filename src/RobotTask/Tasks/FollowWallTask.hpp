#include "../../Utilities.h"
#include "../../Subsystems/DriveTrain/DriveTrain.hpp"
#include "../../Subsystems/FanTurret/FanTurret.hpp"
#include "../RobotTask.hpp"

#ifndef FollowWall_H
#define FollowWall_H

enum FollowWallState {
  FW_FollowWall,
  FW_Turn90,
  FW_SeenGap,
  FW_TurnAroundWall,
  FW_SeenCandleBase
};

class FollowWallTask : public RobotTask {
private:
  typedef RobotTask super;

protected:
  FollowWallState state;
  unsigned long timeLastStateSwitch = 0;

  DriveTrain *_driveTrain;
  FanTurret *_turret;

  void finished();

  const float WALL_DISTANCE = 4;
  const float kP_wallfollow = 0.05;

public:
  FollowWallTask(DriveTrain *driveTrain, FanTurret *turret);

  int getState();

  bool8 isFinished();
  void update();
};

#endif
