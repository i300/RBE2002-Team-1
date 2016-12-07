#include "RobotTaskGroup.hpp"

RobotTaskGroup::RobotTaskGroup() {

}

bool8 RobotTaskGroup::isFinished() {
  return false;
}

void RobotTaskGroup::add(RobotTask *task) {

}

void RobotTaskGroup::update() {

}

void finished() {

}

RobotTaskGroup::~RobotTaskGroup() {
  for (int i = 0; i < TASK_LIST_SIZE; i++) {
    delete tasks[i];
  }
}
