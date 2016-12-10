#include "../../../Utilities.h"
#include "../../../Subsystems/DriveTrain/DriveTrain.hpp"
#include "../../RobotTask.hpp"

#ifndef TurnDegrees_H
#define TurnDegrees_H

class TurnDegreesTask : public RobotTask {
private:
  typedef RobotTask super;

protected:
  DriveTrain *_driveTrain;
  float _degrees;

  void finished();

public:
  TurnDegreesTask(DriveTrain *driveTrain, float degrees);

  bool8 isFinished();
  void update();
};

#endif
