#include "robot.hpp"

/**
 * Reverses chassis drive motors
 * (Allows for backwards control)
 */
void reverseDrive() {
  mtr_dr_tl.setReversed(!is_tl_reversed);
  mtr_dr_tr.setReversed(!is_tr_reversed);
  mtr_dr_br.setReversed(!is_br_reversed);
  mtr_dr_bl.setReversed(!is_bl_reversed);
  is_tl_reversed = !is_tl_reversed;
  is_tr_reversed = !is_tr_reversed;
  is_bl_reversed = !is_bl_reversed;
  is_br_reversed = !is_br_reversed;
}

/**
 * Drive chassis to specified point
 * @param pt [Position to drive to]
 */
void driveToPoint(Point x) {
  profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, x}, "A");
  profileController.setTarget("A");
  profileController.waitUntilSettled();
  profileController.removePath("A");
}

/**
 * Point turn chassis
 * @param angle Specified angle
 */
void turnAngle(QAngle angle) { chassis.turnAngle(angle); }

/**
 * Change roller state
 * @param speed [description]
 */
void setIntakeState(IntakeState st) {
  mtr_intake.moveVelocity(SPD_INTAKE * st);
  intakeState = st;
}

/**
 * Change lift position
 * @param st [description]
 */
void setLiftState(LiftState st) {
  if (clawSonic.get() < 50) {
    liftController.setMaxVelocity(150);
  } else {
    liftController.setMaxVelocity(200);
  }

  liftController.setTarget(liftHeightPresets[st]);
  liftLock = FIXED;
  liftState = st;
  waitUntilLiftSettled();
}

void setConstants(double f, double y, double l) {
  k_speed_forward = f;
  k_speed_yaw = y;
  k_speed_lift = l;
}

void flipCap(bool async) {
  if (clawState == ClawState::ZERO) {
    clawState = ClawState::FLIPPED;
  } else {
    clawState = ClawState::ZERO;
  }
  clawController.setTarget(clawState);
  if (!async) {
    clawController.waitUntilSettled();
  }
}

void lock() {
  // Lock claw
  if (clawLock == CURRENT) {
    clawController.setTarget(clawState);
  }

  // Lock lift
  if (liftLock == CURRENT) {
    liftController.setTarget(mtr_lift.getPosition());
  } else if (liftLock == FIXED) {
    liftController.setTarget(liftHeightPresets[liftState]);
  }
}

void shootBall() {}

void waitUntilLiftSettled() {
  double st = pros::millis();
  while ((!liftController.isSettled() && st < LIFT_MAX_DELAY) && !override) {
    pros::delay(10);
  }
  return;
}

void findCap() {
  double current_tr = mtr_dr_tr.getPosition();
  double current_tl = mtr_dr_tl.getPosition();
  double current_br = mtr_dr_br.getPosition();
  double current_bl = mtr_dr_bl.getPosition();
  double current_sonic = clawSonic.get();
  double left_tr, left_tl, left_br, left_bl;
  double right_tr, right_tl, right_br, right_bl;

  chassis.setMaxVelocity(100);
  chassis.turnAngleAsync(-10_deg);
  while (mtr_dr_tl.getVoltage() > 0) {
    if (clawSonic.get() < SONIC_CLAW_MAX_TURN) {
      left_tr = mtr_dr_tr.getPosition();
      left_tl = mtr_dr_tl.getPosition();
      left_br = mtr_dr_br.getPosition();
      left_bl = mtr_dr_bl.getPosition();
    }
    pros::delay(20);
  }
  chassis.turnAngleAsync(20_deg);
  while (mtr_dr_tl.getVoltage() > 0) {
    if (clawSonic.get() < SONIC_CLAW_MAX_TURN) {
      right_tr = mtr_dr_tr.getPosition();
      right_tl = mtr_dr_tl.getPosition();
      right_br = mtr_dr_br.getPosition();
      right_bl = mtr_dr_bl.getPosition();
    }
    pros::delay(20);
  }

  right_tr = (left_tr + right_tr) / 2;
  right_tl = (left_tl + right_tl) / 2;
  right_br = (left_br + right_br) / 2;
  right_bl = (left_bl + right_bl) / 2;

  chassis.turnAngleAsync(-20_deg);
  while (mtr_dr_tl.getVoltage() > 0) {
    current_tr = mtr_dr_tr.getPosition();
    current_tl = mtr_dr_tl.getPosition();
    current_br = mtr_dr_br.getPosition();
    current_bl = mtr_dr_bl.getPosition();

    if (current_tr < right_tr + 10 && current_tr > right_tr - 10 &&
        current_tl < right_tl + 10 && current_tl > right_tl - 10 &&
        current_br < right_br + 10 && current_br > right_br - 10 &&
        current_bl < right_bl + 10 && current_bl > right_bl - 10) {
          chassis.stop();
    }
    pros::delay(20);
  }
}

void driveIntoCap() {
  chassis.setMaxVelocity(80);
  chassis.moveDistanceAsync(1_m);
  while(clawSonic.get() > 50) {
    pros::delay(20);
  }
  chassis.stop();
}

void descore() {
  // move up
  double current = mtr_lift.getPosition();
  liftController.setTarget(current + 150);
  waitUntilLiftSettled();
  // flip
  flipCap(false);
  // move down
  liftController.setTarget(current);
  waitUntilLiftSettled();
  liftLock = CURRENT;
}

void pullUpLift() {
  liftController.setTarget(liftHeightPresets[LiftState::FOLDED] + 100);
  waitUntilLiftSettled();
  liftController.setTarget(liftHeightPresets[LiftState::GROUND]);
  waitUntilLiftSettled();
}
