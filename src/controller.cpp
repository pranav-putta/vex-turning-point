#include "robot.hpp"

using namespace robot;

location controller::getCurrentPosition() { return currentLoc; }

double controller::driveToPosition(location target) {
  location delta = currentLoc - target;
  // If negative, do some shit to move backwards
  delta >> target.theta.getValue();
  if (delta.y.getValue() < 0) {
    drive_TL.setReversed(true);
    drive_BL.setReversed(true);
    drive_BR.setReversed(false);
    drive_TR.setReversed(false);
  }

  motionProfiler.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{delta.x, delta.y, 0_deg}}, "P");
  motionProfiler.setTarget("P");
  update();

  drive_TL.setReversed(false);
  drive_BL.setReversed(false);
  drive_TL.setReversed(true);
  drive_TR.setReversed(true);
  currentLoc = target;
  return currentLoc % target;
}

void controller::driveOnPlatform() {}

void controller::resetPosition(int corner) { currentLoc << corner; }

void controller::correctPosition(location pos) {}

void controller::setLiftState(LiftState state) {
  if (state == HIGH) {
  } else if (state == MIDDLE) {

  } else if (state == LOW) {
  }
}

void controller::setRollerState(RollerState state) {
  if (state == FORWARD) {
    intake.move(127);
  } else if (state == BACKWARD) {
    intake.move(-127);
  } else {
    intake.move(0);
  }
}

bool controller::resetPuncher() { return true; }

bool controller::firePuncher() { return true; }

void controller::update() {
  currentLoc = odomControl.updateLocation(currentLoc, drive_TL, drive_TR,
                                          drive_BL, drive_BR);
}

void controller::turn(QAngle angle) {
  chassis.turnAngle(angle);
  chassis.waitUntilSettled();
}

void controller::flipCap() {
  // Gear ratio 1:3
  clawController.setTarget(REV * 3);
  clawController.waitUntilSettled();
}

controller* robot::initializeController() {
  controller *c = new controller();
  return c;
}
