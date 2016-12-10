#include "RobotTaskGroup.hpp"

RobotTaskGroup::RobotTaskGroup() {
  numTasks = 0;
}

bool8 RobotTaskGroup::isFinished() {
  return (currentTaskIndex + 1) == numTasks;
}

void RobotTaskGroup::add(RobotTask *task) {
  tasks[numTasks] = task;
  numTasks++;
}

void RobotTaskGroup::update() {
  RobotTask::update();

  Serial.println("Task #: " + String(currentTaskIndex));

  if (currentTaskIndex < numTasks) {
    tasks[currentTaskIndex]->update();
  }

  if (tasks[currentTaskIndex]->isFinished()) {
    Serial.println(String(currentTaskIndex) + " Finished");
    currentTaskIndex++;
  }
}

void RobotTaskGroup::finished() {

}

RobotTaskGroup::~RobotTaskGroup() {
  for (int i = 0; i < TASK_LIST_SIZE; i++) {
    if (tasks[i] != nullptr) {
      delete tasks[i];
    }
  }
}
