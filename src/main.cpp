#include "Arduino.h"
#include "Utilities.h"
#include "RobotMap.h"

#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal.h>

#include "Motor/PololuMotor/PololuMotor.hpp"
#include "IMU/IMU.hpp"
#include "Subsystems/DriveTrain/DriveTrain.hpp"

#include "Subsystems/FanTurret/FanTurret.hpp"

#include "RobotTask/RobotTask.hpp"
#include "RobotTask/Tasks/SystemCheckTask.hpp"

// Subsystems
DriveTrain *driveTrain;
FanTurret *turret;

// Task stuff
RobotTask *currentTask;

// LCD
LiquidCrystal lcd(40, 41, 42, 43, 44, 45);
unsigned long lastWriteTime = 0;
const float lcdFramesPerSecond = 5;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  lcd.begin(16, 2); // Begin LCD
  delay(50); // Hold up, wait a minute
  lcd.clear(); // Clear LCD

  delay(500);

  // Initialize Subsystems
  PololuMotor *left = new PololuMotor(PIN_MOTOR_LEFT_A, PIN_MOTOR_LEFT_B);
  PololuMotor *right = new PololuMotor(PIN_MOTOR_RIGHT_A, PIN_MOTOR_RIGHT_B);

  EncoderCounter *encoders = new EncoderCounter(PIN_SENSOR_ENCODER_SS1, PIN_SENSOR_ENCODER_SS2);

  driveTrain = new DriveTrain(left, right, encoders,
                              PIN_SENSOR_IR_FRONT, PIN_SENSOR_IR_SIDE, PIN_SENSOR_IR_BACK);
  turret = new FanTurret(PIN_SERVO_FAN, PIN_FAN);

  lcd.print("Waiting to start...");

  pinMode(PIN_SENSOR_STARTBUTTON, INPUT_PULLUP);
  while (digitalRead(PIN_SENSOR_STARTBUTTON) == 1) {
    delay(10); // wait to start
  }

  lcd.clear();

  // Start task state-machine at the correct task
  currentTask = new SystemCheckTask(driveTrain, turret);
}

long nextTime = millis() + 2500;
bool8 grabbed = false;

void loop() {
  unsigned long currentTime = millis();

  // Update Subsystems
  driveTrain->update();

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
  float msPerFrame = (1000.0 / lcdFramesPerSecond); // 1000 * (1/FPS)
  if (currentTime > lastWriteTime + msPerFrame) {
    lcd.clear();

    #ifndef DEBUG
      EncoderCounts e = driveTrain->getEncoderCount();
      lcd.setCursor(0, 0);
      lcd.print("L: "); lcd.print(e.left);
      lcd.setCursor(0, 1);
      lcd.print("R: "); lcd.print(e.right);
    #else
      lcd.setCursor(0, 1);
    #endif

    lastWriteTime = currentTime;
  }
}
