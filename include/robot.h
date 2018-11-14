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
#define MAX_ERR 0.01

#define PID_DRIVE_KP 20
#define PID_DRIVE_KI 0
#define PID_DRIVE_KD 3

typedef enum liftstate {GROUND, POST_LOW, POST_HIGH} LiftState;
typedef enum flag {FLAG_LOW, FLAG_HIGH} Flag;

// Drive forward x units, using motion control and PID control
void drive(struct MotionProfile *profile, float dist);

// Turn angle degrees
void turnAngle(float degrees);

void setFlyWheelPower(float power);

void setIntake(bool run);

void setLiftState(LiftState state);

void launchBall(Flag flag);

void driveOntoPlatform(struct MotionProfile *profile, float dist);

#endif