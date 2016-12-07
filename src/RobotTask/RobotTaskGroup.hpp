#include "../Utilities.h"
#include <Arduino.h>

#include "RobotTask.hpp"

#ifndef ROBOT_TASK_GROUP_H
#define ROBOT_TASK_GROUP_H

#define TASK_LIST_SIZE 20

class RobotTaskGroup : public RobotTask {
  RobotTask *tasks[TASK_LIST_SIZE];
  RobotTask *currentTask = nullptr;

protected:
  void finished();

public:
  RobotTaskGroup();
  ~RobotTaskGroup();

  void add(RobotTask *task);
  void update();
  bool8 isFinished();
};

#endif
