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
  FW_DriveThroughGap,
  FW_TurnTowardWall,
  FW_ReFindWall,
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

  bool _returnHome;

  void init();
  void finished();

  const float WALL_DISTANCE = 4;
  const float HOME_THRESHOLD = 5;
  const float kP_wallfollow = 0.05;

public:
  FollowWallTask(DriveTrain *driveTrain, FanTurret *turret, bool returnHome);

  int getState();

  bool8 isFinished();
  void update();
};

#endif
