#include "../../../Utilities.h"
#include "../../../Subsystems/DriveTrain/DriveTrain.hpp"
#include "../../RobotTask.hpp"

#ifndef DriveForwardDistance_H
#define DriveForwardDistance_H

class DriveForwardDistanceTask : public RobotTask {
private:
  typedef RobotTask super;

protected:
  DriveTrain *_driveTrain;
  float _distance;

  void finished();

public:
  DriveForwardDistanceTask(DriveTrain *driveTrain, float distance);

  bool8 isFinished();
  void update();
};

#endif
