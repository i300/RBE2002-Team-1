#include "Arduino.h"
#include "Utilities.h"
#include "RobotMap.h"

#include <SPI.h>
#include <LiquidCrystal.h>

#include "Motor/PololuMotor/PololuMotor.hpp"
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
  PololuMotor *left = new PololuMotor(PIN_MOTOR_LEFT_A, PIN_MOTOR_LEFT_B);
  PololuMotor *right = new PololuMotor(PIN_MOTOR_RIGHT_A, PIN_MOTOR_RIGHT_B);

  EncoderCounter *encoders = new EncoderCounter(PIN_SENSOR_ENCODER_SS1, PIN_SENSOR_ENCODER_SS2);

  driveTrain = new DriveTrain(left, right, encoders);

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
