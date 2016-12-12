#include "RobotTaskGroup.hpp"

RobotTaskGroup::RobotTaskGroup() : RobotTask(TASK_COMMANDGROUP) {
  numTasks = 0;

  for (int i = 0; i < TASK_LIST_SIZE; i++) {
    tasks[i] = 0;
  }
}

bool8 RobotTaskGroup::isFinished() {
  return (currentTaskIndex == numTasks);
}

void RobotTaskGroup::add(RobotTask *task) {
  tasks[numTasks] = task;
  numTasks++;
}

void RobotTaskGroup::update() {
  if (tasks[currentTaskIndex]->isFinished()) {
    Serial.println(String(currentTaskIndex) + " Finished");
    delete tasks[currentTaskIndex];
    tasks[currentTaskIndex] = 0;
    currentTaskIndex++;
  }

  if (tasks[currentTaskIndex]) {
    tasks[currentTaskIndex]->update();
  }

  RobotTask::update();
}

RobotTaskGroup::~RobotTaskGroup() {

}
