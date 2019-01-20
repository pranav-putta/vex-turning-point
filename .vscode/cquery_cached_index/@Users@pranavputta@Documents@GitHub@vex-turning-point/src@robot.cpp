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
}

/**
 * Change lift position
 * @param st [description]
 */
void setLiftState(LiftState st) {
  liftController.setTarget(liftHeightPresets[st]);
  liftLock = FIXED;
  liftState = st;
  liftController.waitUntilSettled();
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

void descore() {
  // move up
  liftController.setTarget(liftHeightPresets[liftState] + 150);
  liftController.waitUntilSettled();
  // flip
  flipCap(false);
  // move down
  liftController.setTarget(liftHeightPresets[liftState]);
  liftController.waitUntilSettled();
  liftLock = FIXED;
}

void pullUpLift() {
  liftController.setTarget(liftHeightPresets[LiftState::FOLDED] + 100);
  liftController.waitUntilSettled();
  liftController.setTarget(liftHeightPresets[LiftState::GROUND]);
  liftController.waitUntilSettled();
}
