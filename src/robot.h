#ifndef ROBOT_H_
#define ROBOT_H_

#include "MotionProfile.h"
#include "PIDController.h"
#include "main.h"

// Robot dimensions
#define WHEELBASE_WIDTH 0.4358
#define WHEEL_RADIUS 0.04

// Motor definitions
#define MTR_L 2
#define MTR_R 3
#define MTR_LIFT_1 4
#define MTR_LIFT_2 5
#define MTR_INTAKE 9
#define MTR_FLY_1 6
#define MTR_FLY_2 7
#define MTR_CLAW 8

// Robot kinematics
#define MAX_VEL 2
#define MAX_ACCEL 3

// Drive forward x units, using motion control and PID control
void drive(struct MotionProfile *profile, float dist);

// Turn angle degrees
void turnAngle(float degrees);

#endif
