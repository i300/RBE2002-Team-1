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
  float _speed;

  EncoderCounts initialE;

  void init();
  void finished();

public:
  DriveForwardDistanceTask(DriveTrain *driveTrain, float distance, float maxSpeed);

  bool8 isFinished();
  void update();
};

#endif
