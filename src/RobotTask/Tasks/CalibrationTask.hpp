#include "../../Utilities.h"
#include "../../Subsystems/DriveTrain/DriveTrain.hpp"
#include "../RobotTask.hpp"

#ifndef CALIBRATION_H
#define CALIBRATION_H

enum CalibrationState {
  CS_FINISHED
};

class CalibrationTask : public RobotTask {
private:
  typedef RobotTask super;

protected:
  CalibrationState state;
  unsigned long timeLastStateSwitch = 0;

  DriveTrain *_driveTrain;

  void finished();

public:
  CalibrationTask(DriveTrain *driveTrain);

  int getState();

  bool8 isFinished();
  void update();
};

#endif
