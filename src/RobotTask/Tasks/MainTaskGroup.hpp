#include "../../Utilities.h"
#include "../../Subsystems/DriveTrain/DriveTrain.hpp"
#include "../../Subsystems/FanTurret/FanTurret.hpp"
#include "../RobotTaskGroup.hpp"

#ifndef MainTaskGroup_H
#define MainTaskGroup_H

class MainTaskGroup : public RobotTaskGroup {
protected:
  DriveTrain *_driveTrain;
  FanTurret *_turret;

  void finished();

public:
  MainTaskGroup(DriveTrain *driveTrain, FanTurret *turret);
};

#endif
