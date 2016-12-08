#include "../Utilities.h"
#include <Arduino.h>

#include "RobotTask.hpp"

#ifndef ROBOT_TASK_GROUP_H
#define ROBOT_TASK_GROUP_H

#define TASK_LIST_SIZE 20

class RobotTaskGroup : public RobotTask {
  RobotTask *tasks[TASK_LIST_SIZE];
  int currentTaskIndex = 0;
  int numTasks = 0;

protected:
  void finished();

public:
  RobotTaskGroup();
  virtual ~RobotTaskGroup();

  void add(RobotTask *task);
  virtual void update();
  bool8 isFinished();
};

#endif
