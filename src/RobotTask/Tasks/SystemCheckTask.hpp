#include "../../Utilities.h"
#include "../../Subsystems/DriveTrain/DriveTrain.hpp"
#include "../../Subsystems/FanTurret/FanTurret.hpp"
#include "../RobotTask.hpp"

#ifndef CALIBRATION_H
#define CALIBRATION_H

enum CalibrationState {
  CS_DRIVE1,
  CS_TURN1,
  CS_DRIVE2,
  CS_FINISHED
};

class SystemCheckTask : public RobotTask {
private:
  typedef RobotTask super;

protected:
  CalibrationState state;
  unsigned long timeLastStateSwitch = 0;

  DriveTrain *_driveTrain;
  FanTurret *_turret;

  void finished();

public:
  SystemCheckTask(DriveTrain *driveTrain, FanTurret *turret);

  int getState();

  bool8 isFinished();
  void update();
};

#endif
