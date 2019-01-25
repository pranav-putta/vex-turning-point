#include "robot.hpp"

void autonomous() {
  initializeAuton();

  if (AUTON_SELECT == 1) {
    autonBT();
  } else if (AUTON_SELECT == 2) {
    autonRT();
  } else if (AUTON_SELECT == 3) {
    autonBB();
  } else if (AUTON_SELECT == 4) {
    autonRB();
  } else if (AUTON_SELECT == 5) {
    subpar();
  }
}

/**
 * Setup robot for autonomous control
 */
void initializeAuton() {
  // Initialize all motors to init settings
  mtr_dr_tl.setReversed(is_tl_reversed);
  mtr_dr_tr.setReversed(is_tr_reversed);
  mtr_dr_br.setReversed(is_br_reversed);
  mtr_dr_bl.setReversed(is_bl_reversed);

  double currentClawPos = mtr_claw.getPosition();
  clawLock = CURRENT;
  liftLock = FREE;
  liftState = LiftState::FOLDED;
}

// top tile, blue
void autonBT() {
  shootBall();
  setIntakeState(IntakeState::FORWARD);
  driveToPoint(Point{48_in, 0_in, 0_deg});
  reverseDrive();
  driveToPoint(Point{49_in, 0_in, 0_deg});
  setIntakeState(IntakeState::IDLE);
  reverseDrive();
  turnAngle(-90_deg);
  driveToPoint(Point{88_in, 8_in, 0_deg});
  pullUpLift();
  reverseDrive();
  driveToPoint(Point{116_in, 16_in, 0_deg});
  turnAngle(90_deg);
  driveToPoint(Point{48_in, 0_in, 0_deg});
  reverseDrive();

  shootBall();
  driveToPoint(Point{88_in, 0_in, 0_deg});
  reverseDrive();
  pullUpLift();
  setLiftState(LiftState::FOLDED);
  driveToPoint(Point{88_in, 0_in, 0_deg});
  reverseDrive();
  driveToPoint(Point{49_in, 0_in, 0_deg});
  setIntakeState(IntakeState::IDLE);
  reverseDrive();
  turnAngle(-90_deg);
  driveToPoint(Point{88_in, 8_in, 0_deg});
  pullUpLift();
  reverseDrive();
  driveToPoint(Point{116_in, 16_in, 0_deg});
  turnAngle(90_deg);
  driveToPoint(Point{48_in, 0_in, 0_deg});
  reverseDrive();
}

// top tile, red
void autonRT() {
  shootBall();
  setIntakeState(IntakeState::FORWARD);
  turnAngle(-90_deg);
  driveToPoint(Point{48_in, 0_in, 0_deg});
  reverseDrive();
  driveToPoint(Point{49_in, 0_in, 0_deg});
  setIntakeState(IntakeState::IDLE);
  reverseDrive();
  turnAngle(90_deg);
  driveToPoint(Point{88_in, 8_in, 0_deg});
  pullUpLift();
  reverseDrive();
  driveToPoint(Point{116_in, 16_in, 0_deg});
  turnAngle(-90_deg);
  driveToPoint(Point{48_in, 0_in, 0_deg});
  reverseDrive();
}

// back tile, blue
void autonBB() {
  setIntakeState(IntakeState::FORWARD);
  driveToPoint(Point{48_in, 0_in, 0_deg});
  pullUpLift();
  turnAngle(90_deg);
  reverseDrive();
  driveToPoint(Point{30_in, 0_in, 0_deg});
  setLiftState(LiftState::GROUND);
  // Move forward until ultrasonic sees it really close
  liftController.setMaxVelocity(100);
  setLiftState(LiftState::FOLDED);
  flipCap();
  driveToPoint(Point{20_in, 0_in, 0_deg});
  setLiftState(LiftState::MIDDLE);
  // Rotate until ultrasonic finds it
  setLiftState(LiftState::MIDDLE);
  reverseDrive();
  driveToPoint(Point{-10_in, 0_in, 0_deg});
  setLiftState(LiftState::GROUND);
  turnAngle(90_deg);
}

void skills() {
  shootBall();
  driveToPoint(Point{88_in, 0_in, 0_deg});
  reverseDrive();
  driveToPoint(Point{44_in, 0_in, 0_deg});
  turnAngle(-90_deg);
  setIntakeState(IntakeState::BACKWARD);
  driveToPoint(Point{44_in, 0_in, 0_deg});
  
}

// back tile, red
void autonRB() {
  setIntakeState(IntakeState::FORWARD);
  driveToPoint(Point{48_in, 0_in, 0_deg});
  pullUpLift();
  turnAngle(-90_deg);
  reverseDrive();
  driveToPoint(Point{30_in, 0_in, 0_deg});
  setLiftState(LiftState::GROUND);
  findCap();
  driveIntoCap();
  liftController.setMaxVelocity(100);
  setLiftState(LiftState::FOLDED);
  flipCap();
  driveToPoint(Point{20_in, 0_in, 0_deg});
  setLiftState(LiftState::MIDDLE);
  // Rotate until ultrasonic finds it
  setLiftState(LiftState::MIDDLE);
  reverseDrive();
  driveToPoint(Point{-10_in, 0_in, 0_deg});
  setLiftState(LiftState::GROUND);
  turnAngle(-90_deg);
}

// sketchy auton
void subpar() {
  driveToPoint(Point{28_in, 0_in, 0_deg});
  reverseDrive();
  driveToPoint(Point{29_in, 0_in, 0_deg});
  reverseDrive();
  turnAngle(38_deg);
  driveToPoint(Point{44_in, 4_in, 0_deg});
  reverseDrive();
  driveToPoint(Point{58_in, 8_in, 0_deg});
  turnAngle(-38_deg);
  driveToPoint(Point{24_in, 0_in, 0_deg});
}
