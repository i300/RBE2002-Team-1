#include "Utilities.h"

#ifndef ROBOTMAP_H
#define ROBOTMAP_H

/* GLOBAL */
static const uint8 ROBOT_ID = 1;

/* ROD GRABBER */
static const uint8 PIN_SERVO_GRABBER = 5;

/* DRIVE TRAIN */
static const uint8 PIN_MOTOR_LEFT_A = 2;
static const uint8 PIN_MOTOR_LEFT_B = 3;
static const uint8 PIN_MOTOR_RIGHT_A = 4;
static const uint8 PIN_MOTOR_RIGHT_B = 5;

/* SENSORS */
static const uint8 PIN_SENSOR_STARTBUTTON = 22;
static const uint8 PIN_SENSOR_ENCODER_SS1 = 28; // SlaveSelect
static const uint8 PIN_SENSOR_ENCODER_SS2 = 29;

#endif
