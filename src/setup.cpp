#include "setup.hpp"

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

void driveToPoint(Point x) {
  profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, x}, "A");
  profileController.setTarget("A");
  profileController.waitUntilSettled();
  profileController.removePath("A");
}

void init() {
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

void arcade() {
  int f =
      master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) * rev * speed_forward;
  int y = -master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) * speed_yaw;

  m_tl.move(f + y);
  m_tr.move(f - y);
  m_bl.move(f + y);
  m_br.move(f - y);
}

void macros() {
  /* Master controls */

  // Lift Control
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
    m_lift1.move(127 * speed_lift);
    m_lift2.move(-127 * speed_lift);
  } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
    m_lift1.move(-127 * speed_lift);
    m_lift2.move(127 * speed_lift);
  } else {
    m_lift1.move(0);
  }

  // Lift presets
  // TODO: finish thi shit
  // TOP
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
    liftController.moveDistanceAsync(20_in);
  }
  // MIDDLE
  else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
    liftController.moveDistanceAsync(20_in);
  }
  // BOTTOM
  else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
    liftController.moveDistanceAsync(20_in);
  }
  // SLIGHTLY UP
  else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
    liftController.moveDistanceAsync(20_in);
  }

  // Flip Cap
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
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
    // TODO: SET this up
  }
}

void flipCap(bool async) {
  currentClawPos = currentClawPos == 0 ? 92 : 0;
  clawController.setTarget(currentClawPos);
  if (!async) {
    clawController.waitUntilSettled();
  }
}
