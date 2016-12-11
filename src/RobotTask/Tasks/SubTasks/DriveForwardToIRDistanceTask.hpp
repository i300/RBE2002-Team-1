#include "../../../Utilities.h"
#include "../../../Subsystems/DriveTrain/DriveTrain.hpp"
#include "../../RobotTask.hpp"

#ifndef DriveForwardToIRDistance_H
#define DriveForwardToIRDistance_H

class DriveForwardToIRDistanceTask : public RobotTask {
private:
  typedef RobotTask super;

protected:
  DriveTrain *_driveTrain;
  float _distance;

  void init();
  void finished();

public:
  DriveForwardToIRDistanceTask(DriveTrain *driveTrain, float distance);

  bool8 isFinished();
  void update();
};

#endif
