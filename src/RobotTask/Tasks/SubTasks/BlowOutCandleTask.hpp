#include "../../../Utilities.h"
#include "../../../Subsystems/DriveTrain/DriveTrain.hpp"
#include "../../../Subsystems/FanTurret/FanTurret.hpp"
#include "../../RobotTask.hpp"

#ifndef BlowOutCandle_H
#define BlowOutCandle_H

#define NUM_ANGLES 181

class BlowOutCandleTask : public RobotTask {
private:
  typedef RobotTask super;

protected:
  DriveTrain *_driveTrain;
  FanTurret *_turret;

  int currentAngle = 0;
  int candleValues[NUM_ANGLES];
  bool candleFound = false;
  bool candleOut = false;
  int blowAttempts = 0;
  unsigned long maxBlowTime = 0;

  void init();
  void finished();

public:
  BlowOutCandleTask(DriveTrain *driveTrain, FanTurret *turret);

  bool8 isFinished();
  void update();
};

#endif
