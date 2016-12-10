#include "../Utilities.h"
#include <Arduino.h>

/*
 * RobotTask
 * Base class that defines the robot's current "task"
 *
 */

#ifndef ROBOTTASK_H
#define ROBOTTASK_H

enum RobotTaskType {
  NO_TASK,
  TASK_UNDEFINED,
  SYSTEM_CHECK,
  CALIBRATION,
  FOLLOW_WALL,
  DRIVE_TO_CANDLE
};

class RobotTask {

protected:
  RobotTaskType _type;

  bool8 _finished;

  unsigned long _timeStarted;
  unsigned long getTimeStarted();

  virtual void finished();

public:
  RobotTask();
  RobotTask(RobotTaskType type);
  virtual ~RobotTask() {};

  RobotTaskType getType();
  virtual bool8 isFinished();
  virtual void update();

  virtual int getState();
};

#endif
