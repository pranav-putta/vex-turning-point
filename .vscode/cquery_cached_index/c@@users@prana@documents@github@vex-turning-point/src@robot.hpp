#include "main.h"

using namespace okapi;

// Chassis Definitions
#define WHEEL_SIZE 4_in
#define BASE_SIZE 16.75_in

// Motor definitions
#define MTR_TL 1
#define MTR_TR 2
#define MTR_BL 11
#define MTR_BR 15
#define MTR_LIFT_1 10
#define MTR_LIFT_2 12
#define MTR_CLAW 13
#define MTR_INTAKE 14

#define AUTON_SELECT 1

#define LIFT_H_HIGH 700
#define LIFT_H_MID 500
#define LIFT_H_GROUND -152
#define LIFT_H_TARGET 20

enum LockState { LOCK_FREE, LOCK_CURRENT, LOCK_FIXED };

enum LiftState { LIFT_HIGH, LIFT_MID, LIFT_GROUND, LIFT_TARGET, LIFT_FOLD };

// Control function definitions
void reverse();
void driveToPoint(Point x);
void turnAngle(QAngle angle);
void initAuton();
void initOpControl();
void arcade();
void macros();
void lock();
void flipCap(bool async = true);
void descore();
void pullUpLift();
void setRoller(double speed);
double getLiftHeight();

// Autonomous functions
void autonBT();
void subpar();
void autonRT();
void autonBB();
void autonRB();
