#include "../../Utilities.h"
#include "../../Subsystems/DriveTrain/DriveTrain.hpp"
#include "../../Subsystems/FanTurret/FanTurret.hpp"
#include "../RobotTaskGroup.hpp"

#ifndef DriveToCandle_H
#define DriveToCandle_H

class DriveToCandleTask : public RobotTaskGroup {
public:
  DriveToCandleTask(DriveTrain *driveTrain, FanTurret *turret);
};

#endif
