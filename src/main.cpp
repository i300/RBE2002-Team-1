#include "Arduino.h"
#include "Utilities.h"
#include "RobotMap.h"

#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <TimerOne.h>

#include "Motor/PololuMotor/PololuMotor.hpp"
#include "IMU/IMU.hpp"
#include "Subsystems/DriveTrain/DriveTrain.hpp"

#include "Subsystems/FanTurret/FanTurret.hpp"

#include "RobotTask/RobotTask.hpp"
#include "RobotTask/Tasks/SystemCheckTask.hpp"
#include "RobotTask/Tasks/MainTaskGroup.hpp"

#define DEBUG 1

// Subsystems
DriveTrain *driveTrain;
FanTurret *turret;

// Sensors
IMU *imu;

// Task stuff
MainTaskGroup *task;

// LCD
LiquidCrystal lcd(40, 41, 42, 43, 44, 45);
unsigned long lastWriteTime = 0;
const float lcdFramesPerSecond = 5;

// Robot State Variables
boolean stopped = false;

// Localization Prototype
void localize();
volatile EncoderCounts currentE = {0};
volatile EncoderCounts lastE = {0};
volatile float x=0, y=0, theta=0;
volatile unsigned long dTime = 0;
unsigned long lastTimeUpdated = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  lcd.begin(16, 2); // Begin LCD
  delay(50); // Hold up, wait a minute
  lcd.clear(); // Clear LCD

  lcd.print("Calibrating IMU");

  imu = new IMU();
  imu->init();

  // Initialize Subsystems
  PololuMotor *left = new PololuMotor(PIN_MOTOR_LEFT_A, PIN_MOTOR_LEFT_B);
  PololuMotor *right = new PololuMotor(PIN_MOTOR_RIGHT_A, PIN_MOTOR_RIGHT_B);

  EncoderCounter *encoders = new EncoderCounter(PIN_SENSOR_ENCODER_SS1, PIN_SENSOR_ENCODER_SS2);

  driveTrain = new DriveTrain(left, right, encoders, imu,
                              PIN_SENSOR_IR_FRONT, PIN_SENSOR_IR_SIDE, PIN_SENSOR_IR_BACK);
  turret = new FanTurret(PIN_SERVO_FAN, PIN_FAN, PIN_SENSOR_CANDLE_SENSOR);

  lcd.clear();
  lcd.print("Waiting to start");

  pinMode(PIN_SENSOR_STARTBUTTON, INPUT_PULLUP);
  while (digitalRead(PIN_SENSOR_STARTBUTTON) == 1) {
    delay(10); // wait to start
  }

  delay(250);

  lcd.clear();

  task = new MainTaskGroup(driveTrain, turret);
  //currentTask = new FollowWallTask(driveTrain, turret);
  //currentTask = new SystemCheckTask(driveTrain, turret);

  // Initialize Interrupt for Localization
  //Timer1.initialize(10000); // every 10ms
  //Timer1.attachInterrupt(localize);
}

void loop() {
  unsigned long currentTime = millis();

  bool stoppedButton = digitalRead(PIN_SENSOR_STARTBUTTON) == 0;
  if (stoppedButton) {
    stopped = true;
  }

  if (stopped) {
    driveTrain->stop();
    driveTrain->update();
    turret->fanOff();

    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print("E-STOP");
    delay(10);
    return;
  }

  // Update Subsystems
  driveTrain->update();
  imu->update();

  currentE = driveTrain->getEncoderCount();

  // Update current task
  if (task) {
    task->update();

    if (task->isFinished()) {
      delete task;
      task = 0;
    }
  }

  if (currentTime > lastTimeUpdated + 10) {
    localize();

    lastTimeUpdated = currentTime;
  }

  // Write to LCD
  float msPerFrame = (1000.0 / lcdFramesPerSecond); // 1000 * (1/FPS)
  if (currentTime > lastWriteTime + msPerFrame) {
    lcd.clear();

    #ifdef DEBUG
      lcd.setCursor(0, 0);
      //EncoderCounts e = driveTrain->getEncoderCount();
      //lcd.print("L: "); lcd.print(e.left);
      //lcd.setCursor(0, 1);
      //lcd.print("R: "); lcd.print(e.right);
      //lcd.print("IR_F: "); lcd.print(driveTrain->getIRReading(IR_FRONT));
      //lcd.setCursor(0, 1);
      //lcd.print("IR_S: "); lcd.print(driveTrain->getIRReading(IR_SIDE));
      //lcd.print("IMU: "); lcd.print(imu->getGyroReading().z);
      //lcd.setCursor(0, 1);
      //lcd.print("Candle: " + String(analogRead(PIN_SENSOR_CANDLE_SENSOR)));
      lcd.print("x: " + String(x));
      lcd.setCursor(0, 1);
      lcd.print("y: " + String(y));
    #else
      lcd.setCursor(0, 1);
    #endif

    lastWriteTime = currentTime;
  }
}

void localize() {
  EncoderCounts _lastE = {0};
  _lastE.left = lastE.left;
  _lastE.right = lastE.right;

  EncoderCounts de;
  de.left = currentE.left - _lastE.left;
  de.right = currentE.right - _lastE.right;

  float ds = (de.right + de.left) / 2.0;
  float dTheta = (de.right - de.left) / ROBOT_DRIVE_TRACK;

  float _theta = theta;

  float dx = ds * cos(_theta + (dTheta / 2.0));
  float dy = ds * sin(_theta + (dTheta / 2.0));

  x += dx;
  y += dy;
  theta += dTheta;

  lastE.left = currentE.left;
  lastE.right = currentE.right;
}
