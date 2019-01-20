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
  driveToPoint(Point{48_in, 0_in, 0_deg});
  reverseDrive();
  driveToPoint(Point{49_in, 0_in, 0_deg});
  reverseDrive();
  turnAngle(-90_deg);
  driveToPoint(Point{88_in, 8_in, 0_deg});
  reverseDrive();
  driveToPoint(Point{116_in, 16_in, 0_deg});
  turnAngle(90_deg);
  driveToPoint(Point{48_in, 0_in, 0_deg});
  reverseDrive();
}

// top tile, red
void autonRT() {
  driveToPoint(Point{48_in, 0_in, 0_deg});
  reverseDrive();
  driveToPoint(Point{49_in, 0_in, 0_deg});
  reverseDrive();
  turnAngle(90_deg);
  driveToPoint(Point{88_in, 8_in, 0_deg});
  reverseDrive();
  driveToPoint(Point{116_in, 16_in, 0_deg});
  turnAngle(-90_deg);
  driveToPoint(Point{48_in, 0_in, 0_deg});
  reverseDrive();
}

// back tile, blue
void autonBB() {

}

// back tile, red
void autonRB() {

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
