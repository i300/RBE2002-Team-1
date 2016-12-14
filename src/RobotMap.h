#include "Utilities.h"

#ifndef ROBOTMAP_H
#define ROBOTMAP_H

/* GLOBAL */
static const uint8 ROBOT_ID = 1;
static const float ROBOT_DRIVE_TRACK = (4.63*2);

/* FAN */
static const uint8 PIN_SERVO_FAN = 6;
static const uint8 PIN_FAN = 18;

/* DRIVE TRAIN */
static const uint8 PIN_MOTOR_LEFT_A = 2;
static const uint8 PIN_MOTOR_LEFT_B = 3;
static const uint8 PIN_MOTOR_RIGHT_A = 8;
static const uint8 PIN_MOTOR_RIGHT_B = 9;

/* LEDS */
static const uint8 PIN_LED_CANDLE_FOUND = 11;
static const uint8 PIN_LED_CANDLE_OUT = 12;

/* SENSORS */
static const uint8 PIN_SENSOR_STARTBUTTON = 26;
static const uint8 PIN_SENSOR_ENCODER_SS1 = 28;
static const uint8 PIN_SENSOR_ENCODER_SS2 = 29;

static const uint8 PIN_SENSOR_IR_FRONT = A10;
static const uint8 PIN_SENSOR_IR_SIDE = A11;
static const uint8 PIN_SENSOR_IR_BACK = A0;

static const uint8 PIN_SENSOR_CANDLE_SENSOR = A1;

#endif
