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

#define AUTON_SELECT 1

#define LIFT_H_HIGH 400
#define LIFT_H_MID 200
#define LIFT_H_GROUND 100
#define LIFT_H_TARGET 200

enum LockState { LOCK_FREE, LOCK_CURRENT, LOCK_FIXED };

enum LiftState { LIFT_HIGH, LIFT_MID, LIFT_GROUND, LIFT_TARGET, LIFT_FOLD };

// Variables
bool is_tl_reversed = true;
bool is_bl_reversed = true;
bool is_br_reversed = false;
bool is_tr_reversed = false;

// Chassis Variables
int rev = 1;
double speed_forward = 1;
double speed_yaw = 0.8;
double speed_lift = 1;

int f, y;

// Lock Variables
LockState clawLock = LOCK_FREE;
LockState liftLock = LOCK_FREE;
LiftState liftPos = LIFT_FOLD;
double currentClawPos = 0.0;

// Motor Definitions
Motor m_tl(MTR_TL);
Motor m_bl(MTR_BL);
Motor m_tr(MTR_TR);
Motor m_br(MTR_BR);
Motor m_lift1(MTR_LIFT_1);
Motor m_lift2(MTR_LIFT_2);
Motor m_claw(MTR_CLAW);

// Control Systems
auto chassis = ChassisControllerFactory::create(
    {-1, -11},                            // Left motors
    {2, 15},                              // Right motors
    okapi::AbstractMotor::gearset::green, // Torque gearset
    {WHEEL_SIZE, BASE_SIZE} // 4 inch wheels, 16.75 inch wheelbase width
);

auto profileController = AsyncControllerFactory::motionProfile(
    1.0,    // Maximum linear velocity of the Chassis in m/s
    2.0,    // Maximum linear acceleration of the Chassis in m/s/s
    10.0,   // Maximum linear jerk of the Chassis in m/s/s/s
    chassis // Chassis Controller
);

// auto liftController = AsyncControllerFactory::posIntegrated({MTR_LIFT_1,
// MTR_LIFT_2});
auto liftController = ChassisControllerFactory::create(
    MTR_LIFT_1, MTR_LIFT_2, okapi::AbstractMotor::gearset::green,
    {1_in, 10_in});
auto clawController = AsyncControllerFactory::posIntegrated(MTR_CLAW, 50);

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller slave(pros::E_CONTROLLER_PARTNER);

// Control function definitions
void reverse();
void driveToPoint(Point x);
void init();
void arcade();
void macros();
void lock();
void flipCap(bool async = true);

// Autonomous functions
void autonBT();
void subpar();
void autonRT();
void autonBB();
void autonRB();
