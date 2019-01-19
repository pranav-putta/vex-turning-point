#include "robot.hpp"


// Variables
bool is_tl_reversed = true;
bool is_bl_reversed = true;
bool is_br_reversed = false;
bool is_tr_reversed = false;

bool is_rolling = false;

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

bool liftPressed = false;

// Motor Definitions
Motor m_tl(MTR_TL);
Motor m_bl(MTR_BL);
Motor m_tr(MTR_TR);
Motor m_br(MTR_BR);
Motor m_lift1(MTR_LIFT_1);
Motor m_lift2(MTR_LIFT_2);
Motor m_claw(MTR_CLAW);
Motor m_intake(MTR_INTAKE);

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

auto liftController = AsyncControllerFactory::posIntegrated({MTR_LIFT_1, -MTR_LIFT_2}, 150);
auto clawController = AsyncControllerFactory::posIntegrated(MTR_CLAW, 50);

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller slave(pros::E_CONTROLLER_PARTNER);


void reverse() {
  m_tl.setReversed(!is_tl_reversed);
  m_tr.setReversed(!is_tr_reversed);
  m_br.setReversed(!is_br_reversed);
  m_bl.setReversed(!is_bl_reversed);
  is_tl_reversed = !is_tl_reversed;
  is_tr_reversed = !is_tr_reversed;
  is_bl_reversed = !is_bl_reversed;
  is_br_reversed = !is_br_reversed;
}

void driveToPoint(Point x)  {
  profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, x}, "A");
  profileController.setTarget("A");
  profileController.waitUntilSettled();
  profileController.removePath("A");
}

void turnAngle(QAngle angle) {
  chassis.turnAngle(angle);
}

void initAuton() {
  // Initialize all motors to init settings
  m_tl.setReversed(is_tl_reversed);
  m_tr.setReversed(is_tr_reversed);
  m_br.setReversed(is_br_reversed);
  m_bl.setReversed(is_bl_reversed);

  double currentClawPos = m_claw.getPosition();
  clawLock = LOCK_CURRENT;
  liftLock = LOCK_FREE;
  liftPos = LIFT_FOLD;
}

void initOpControl() {
  // Initialize all motors to init settings
  is_tl_reversed = false;
  is_bl_reversed = false;
  is_tr_reversed = true;
  is_br_reversed = true;
  m_tl.setReversed(is_tl_reversed);
  m_tr.setReversed(is_tr_reversed);
  m_br.setReversed(is_br_reversed);
  m_bl.setReversed(is_bl_reversed);

  double currentClawPos = m_claw.getPosition();
  clawLock = LOCK_CURRENT;
  liftLock = LOCK_FREE;
  liftPos = LIFT_FOLD;

  speed_lift = 0.3;
}

void arcade() {
  int f =
      master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) * rev * speed_forward;
  int y = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) * speed_yaw;

  m_tl.move(f + y);
  m_tr.move(f - y);
  m_bl.move(f + y);
  m_br.move(f - y);
}

void macros() {
  /* Master controls */

  // Lift Macros
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
      pullUpLift();
    }

    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
      descore();
    }

  // Intake Macros
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
      if (!is_rolling) {
      setRoller(0.6);
      is_rolling = true;
    } else {
      is_rolling = false;
      setRoller(0.0);
    }
    }

  // Lift Control
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
    liftPressed = true;
    liftLock = LOCK_FREE;
    m_lift1.move(127 * speed_lift);
    m_lift2.move(127 * speed_lift);
  } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
    liftPressed = true;
    liftLock = LOCK_FREE;
    m_lift1.move(-127 * speed_lift);
    m_lift2.move(-127 * speed_lift);
  } else {
    if (liftPressed) {
      liftLock = LOCK_CURRENT;
      liftPressed = false;
    }
    m_lift1.move(0);
    m_lift2.move(0);
  }

  // Lift presets
  // TODO: finish thi shit
  // TOP
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
    liftController.setTarget(LIFT_H_HIGH);
    liftLock = LOCK_FIXED;
    liftPos = LIFT_HIGH;
    liftController.waitUntilSettled();
  }
  // MIDDLE
  else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
    liftController.setTarget(LIFT_H_MID);
    liftLock = LOCK_FIXED;
    liftPos = LIFT_MID;
    liftController.waitUntilSettled();
  }
  // BOTTOM
  else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
    liftController.setTarget(LIFT_H_GROUND);
    liftLock = LOCK_FIXED;
    liftPos = LIFT_GROUND;
    liftController.waitUntilSettled();
   }
  // SLIGHTLY UP
  else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
    liftController.setTarget(LIFT_H_TARGET);
    liftLock = LOCK_FIXED;
    liftPos = LIFT_TARGET;
    liftController.waitUntilSettled();
  }

  // Flip Cap
  if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
    flipCap();
  }

  /* Slave Controls */

  //  Reverse drive
  if (slave.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
    rev = -rev;
  }

  // Change Speeds
  // Regular speed
  if (slave.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
    speed_forward = 1;
    speed_yaw = 0.8;
    speed_lift = 0.6;
    slave.print(1, 1, "%s", "FREE SPD");
    master.print(1, 1, "%s", "FREE SPD");
  }
  // Holding Cap speed
  else if (slave.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
    speed_forward = 0.75;
    speed_yaw = 0.7;
    speed_lift = 0.5;
    slave.print(1, 1, "%s", "CAP SPD");
    master.print(1, 1, "%s", "CAP SPD");
  }
  // Goal post speed
  else if (slave.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
    speed_forward = 0.5;
    speed_yaw = 0.25;
    speed_lift = 0.25;
    slave.print(1, 1, "%s", "GOAL SPD");
    master.print(1, 1, "%s", "GOAL SPD");
  }

  // Descore Autonomous
  if (slave.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
    // TODO: FINISH THIS
    // Raise lift
    flipCap(false);
    // Lift back down
  }

}

void lock() {
  if (clawLock == LOCK_CURRENT) {
    clawController.setTarget(currentClawPos);
  }

  if (liftLock == LOCK_CURRENT) {
    liftController.setTarget((m_lift1.getPosition() + m_lift2.getPosition()) / 2);
  } else if (liftLock == LOCK_FIXED) {
    liftController.setTarget(getLiftHeight());
  }
}

double getLiftHeight() {
  if (liftPos == LIFT_HIGH) {
    return LIFT_H_HIGH;
  } else if (liftPos == LIFT_MID) {
    return LIFT_H_MID;
  } else if (liftPos == LIFT_GROUND) {
    return LIFT_H_GROUND;
  } else if (liftPos == LIFT_TARGET) {
    return LIFT_H_TARGET;
  }

  return 0;
}

void flipCap(bool async) {
  currentClawPos = currentClawPos == 0 ? 90 : 0;
  clawController.setTarget(currentClawPos);
  if (!async) {
    clawController.waitUntilSettled();
  }
}

void descore() {
  liftLock = LOCK_FREE;
  liftController.setTarget(getLiftHeight() + 150);
  liftController.waitUntilSettled();
  flipCap(false);
  liftController.setTarget(getLiftHeight());
  liftController.waitUntilSettled();
  liftLock = LOCK_FIXED;
}

void setRoller(double speed) {
  m_intake.move(127 * speed);
}

void pullUpLift() {
  liftController.setTarget(100);
  liftController.waitUntilSettled();
  liftController.setTarget(-150);
  liftController.waitUntilSettled();
}
