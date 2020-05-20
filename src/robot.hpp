#include "main.h"

using namespace okapi;

// Chassis Definitions
#define WHEEL_SIZE 4_in
#define BASE_SIZE 16.75_in

#define CHASSIS_VEL 1.0
#define CHASSIS_ACCEL 2.0
#define CHASSIS_JERK 10.0

// Motor definitions
#define MTR_TL 1
#define MTR_TR 2
#define MTR_BL 11
#define MTR_BR 15
#define MTR_LIFT 10
#define MTR_CLAW 13
#define MTR_INTAKE 14
#define MTR_PUNCHER 16

#define SONIC_CLAW_TOP 1
#define SONIC_CLAW_BOT 2

#define LIFT_MAX_DELAY 5000

// Motor Speed Definitions
#define SPD_LIFT 200
#define SPD_CLAW 50
#define SPD_INTAKE 300

// Selected autonomous
#define AUTON_SELECT 1

// Lift height presets
#define LIFT_H_HIGH 700
#define LIFT_H_MID 500
#define LIFT_H_GROUND -152
#define LIFT_H_TARGET 20
#define LIFT_H_FOLDED 0

// Ultrasonic setConstants
#define SONIC_CLAW_MAX_TURN 100

// Enum definitions
enum LockState { FREE, CURRENT, FIXED };
enum IntakeState { FORWARD = 1, BACKWARD = -1, IDLE = 0 };
enum LiftState { TOP = 0, MIDDLE = 1, GROUND = 2, FOLDED = 3 };
enum PuncherState { CHARGING, REST };
enum ClawState { ZERO = 0, FLIPPED = 180 };

// Odometry class definition
struct odomData {
  long enc_tl, enc_tr, enc_bl, enc_br;
};

class odometry {
private:
  Point calculatedPosition;
};

extern odometry odom;

// Global variable definitions

// Drive variables
extern bool is_tl_reversed;
extern bool is_bl_reversed;
extern bool is_br_reversed;
extern bool is_tr_reversed;

extern bool override;

extern int direction;
extern double forward, yaw;
extern double k_speed_forward;
extern double k_speed_yaw;
extern double k_speed_lift;

// Puncher system

// Lock system
extern LockState clawLock;
extern LockState liftLock;

// Lift system
extern LiftState liftState;
extern IntakeState intakeState;
extern PuncherState puncherState;
extern ClawState clawState;

extern double liftHeightPresets[4];

// Motors
extern Motor mtr_dr_tl;
extern Motor mtr_dr_bl;
extern Motor mtr_dr_tr;
extern Motor mtr_dr_br;
extern Motor mtr_lift;
extern Motor mtr_claw;
extern Motor mtr_intake;
extern Motor mtr_puncher;

// Control Systems
extern ChassisControllerIntegrated chassis;
extern AsyncMotionProfileController profileController;
extern AsyncPosIntegratedController liftController;
extern AsyncPosIntegratedController clawController;

extern Controller master;
extern Controller slave;

// Sensors
extern ADIUltrasonic clawSonic;

// Master Control
extern ControllerButton unfoldLiftButton;
extern ControllerButton descoreButton;
extern ControllerButton clawFlipButton;
extern ControllerButton intakeStateButton;
extern ControllerButton liftUpButton;
extern ControllerButton liftDownButton;
extern ControllerButton liftPresetHighButton;
extern ControllerButton liftPresetMidButton;
extern ControllerButton liftPresetGroundButton;
extern ControllerButton liftPresetRestButton;

// Slave Control
extern ControllerButton reverseButton;
extern ControllerButton regularSpeedButton;
extern ControllerButton holdingSpeedButton;
extern ControllerButton goalPostSpeedButton;

// Initialization functions

void initializeRobot();
void initializeAuton();
void initializeOpControl();

// ----------------------------------------------------------

// Robot function definitions

void reverseDrive();
void driveToPoint(Point pt);
void turnAngle(QAngle angle);
void setIntakeState(IntakeState st);
void setLiftState(LiftState st);
void shootBall();
void setConstants(double forward, double yaw, double lift);
void flipCap(bool async = true);
void lock();
void descore();
void pullUpLift();
void waitUntilLiftSettled();
void findCap();
void driveIntoCap();
odomData generateOdometryData();
void updateOdometry();

// ----------------------------------------------------------

// Driver Control definitions

void arcade();
void master_macros();
void slave_macros();

// -------------------------------------------

// Autonomous functions
void autonBT();
void subpar();
void autonRT();
void autonBB();
void autonRB();
void skills();
