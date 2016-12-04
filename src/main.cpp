#include "Arduino.h"
#include "Utilities.h"
#include "RobotMap.h"

#include <LiquidCrystal.h>

#include "Subsystems/DriveTrain/DriveTrain.hpp"

#include "RobotTask/RobotTask.hpp"
#include "RobotTask/Tasks/CalibrationTask.hpp"

// Subsystems
DriveTrain *driveTrain;

// Task stuff
RobotTask *currentTask;

// LCD
LiquidCrystal lcd(40, 41, 42, 43, 44, 45);
unsigned long lastWriteTime = 0;
const float lcdFramesPerSecond = 30;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  lcd.begin(16, 2); // Begin LCD
  delay(50); // Hold up, wait a minute
  lcd.clear(); // Clear LCD

  delay(500);

  lcd.print("Waiting to start...");

  pinMode(PIN_SENSOR_STARTBUTTON, INPUT_PULLUP);
  while (digitalRead(PIN_SENSOR_STARTBUTTON) == 1) {
    delay(10); // wait to start
  }

  lcd.clear();

  // Initialize Subsystems
  //driveTrain = new DriveTrain(left, right);

  // Start task state-machine at the correct task
  currentTask = new CalibrationTask(driveTrain);
}

long nextTime = millis() + 2500;
bool8 grabbed = false;

void loop() {
  unsigned long currentTime = millis();

  // Update Subsystems
  // ...

  // Update current task
  currentTask->update();

  // Update state machine if task is finished
  RobotTaskType taskType = currentTask->getType();
  if (currentTask->isFinished()) {
    // Delete old task off the heap
    delete currentTask;

    switch (taskType) {

      case NO_TASK:
        // Nothing to see here...
        break;

      case CALIBRATION:
        //currentTask = new PickUpFromReactorTask(driveTrain, rodGrabber, fieldController);
        break;

      default:
        //currentTask = new RobotTask();
        break;
    }
  }

  // Write to LCD
  float msPerFrame = (1000 / lcdFramesPerSecond); // 1000 * (1/FPS)
  if (currentTime > lastWriteTime + msPerFrame) {
    lcd.clear();

    #ifndef DEBUG

    #else
      lcd.setCursor(0, 1);
    #endif

    lastWriteTime = currentTime;
  }
}
