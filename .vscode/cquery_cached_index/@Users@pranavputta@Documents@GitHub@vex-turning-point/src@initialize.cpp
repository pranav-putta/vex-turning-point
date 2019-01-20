#include "robot.hpp"

// Global variables initialization

// Drive variables
bool is_tl_reversed = true;
bool is_bl_reversed = true;
bool is_br_reversed = false;
bool is_tr_reversed = false;

int direction = 1, forward, yaw;
double k_speed_forward = 1;
double k_speed_yaw = 0.8;
double k_speed_lift = 1;

// Puncher system

// Lock system
LockState clawLock = LockState::FREE;
LockState liftLock = LockState::FREE;

// Lift system
LiftState liftState = LiftState::FOLDED;
IntakeState intakeState = IntakeState::IDLE;
PuncherState puncherState = PuncherState::REST;
ClawState clawState = ClawState::ZERO;

double liftHeightPresets[] = {LIFT_H_HIGH, LIFT_H_MID, LIFT_H_GROUND,
                              LIFT_H_FOLDED};

// Motors
Motor mtr_dr_tl(MTR_TL);
Motor mtr_dr_bl(MTR_BL);
Motor mtr_dr_tr(MTR_TR);
Motor mtr_dr_br(MTR_BR);
Motor mtr_lift(MTR_LIFT);
Motor mtr_claw(MTR_CLAW);
Motor mtr_intake(MTR_INTAKE);
Motor mtr_puncher(MTR_PUNCHER);

// Control systems
ChassisControllerIntegrated chassis = ChassisControllerFactory::create(
    {-MTR_TL, -MTR_BL},                   // Left motors
    {MTR_TR, MTR_BR},                     // Right motors
    okapi::AbstractMotor::gearset::green, // Torque gearset
    {WHEEL_SIZE, BASE_SIZE} // 4 inch wheels, 16.75 inch wheelbase width
);

AsyncMotionProfileController profileController =
    AsyncControllerFactory::motionProfile(
        CHASSIS_VEL,   // Maximum linear velocity of the Chassis in m/s
        CHASSIS_ACCEL, // Maximum linear acceleration of the Chassis in m/s/s
        CHASSIS_JERK,  // Maximum linear jerk of the Chassis in m/s/s/s
        chassis        // Chassis Controller
    );

AsyncPosIntegratedController liftController =
    AsyncControllerFactory::posIntegrated(MTR_LIFT, SPD_LIFT);
AsyncPosIntegratedController clawController =
    AsyncControllerFactory::posIntegrated(MTR_CLAW, SPD_CLAW);

Controller master(ControllerId::master);
Controller nigga(ControllerId::partner);

// Master
ControllerButton unfoldLiftButton(ControllerDigital::B);
ControllerButton descoreButton(ControllerDigital::A);
ControllerButton clawFlipButton(ControllerDigital::R1);
ControllerButton intakeStateButton(ControllerDigital::R2);
ControllerButton liftUpButton(ControllerDigital::L1);
ControllerButton liftDownButton(ControllerDigital::L2);
ControllerButton liftPresetHighButton(ControllerDigital::up);
ControllerButton liftPresetMidButton(ControllerDigital::right);
ControllerButton liftPresetGroundButton(ControllerDigital::down);
ControllerButton liftPresetRestButton(ControllerDigital::left);

// Slave
ControllerButton reverseButton(ControllerId::partner, ControllerDigital::R1);
ControllerButton regularSpeedButton(ControllerId::partner, ControllerDigital::up);
ControllerButton holdingSpeedButton(ControllerId::partner, ControllerDigital::right);
ControllerButton goalPostSpeedButton(ControllerId::partner, ControllerDigital::down);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  pros::lcd::initialize();
  initializeRobot();
}

/**
 * Initialize robot
 */
void initializeRobot() {
  mtr_claw.setGearing(AbstractMotor::gearset::green);
  mtr_lift.setGearing(AbstractMotor::gearset::green);
  mtr_puncher.setGearing(AbstractMotor::gearset::green);
  mtr_intake.setGearing(AbstractMotor::gearset::blue);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
