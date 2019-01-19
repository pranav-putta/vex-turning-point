#include "setup.hpp"

void autonomous() {
  init();

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

// top tile, blue
void autonBT() {
  driveToPoint(Point{48_in, 0_in, 0_deg});
  reverse();
  driveToPoint(Point{49_in, 0_in, 0_deg});
  reverse();
  chassis.turnAngle(-90_deg);
  driveToPoint(Point{88_in, 8_in, 0_deg});
  reverse();
  driveToPoint(Point{116_in, 16_in, 0_deg});
  chassis.turnAngle(90_deg);
  driveToPoint(Point{48_in, 0_in, 0_deg});
  reverse();
}

// top tile, red
void autonRT() {
  driveToPoint(Point{48_in, 0_in, 0_deg});
  reverse();
  driveToPoint(Point{49_in, 0_in, 0_deg});
  reverse();
  chassis.turnAngle(90_deg);
  driveToPoint(Point{88_in, 8_in, 0_deg});
  reverse();
  driveToPoint(Point{116_in, 16_in, 0_deg});
  chassis.turnAngle(-90_deg);
  driveToPoint(Point{48_in, 0_in, 0_deg});
  reverse();
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
  reverse();
  driveToPoint(Point{29_in, 0_in, 0_deg});
  reverse();
  chassis.turnAngle(38_deg);
  driveToPoint(Point{44_in, 4_in, 0_deg});
  reverse();
  driveToPoint(Point{58_in, 8_in, 0_deg});
  chassis.turnAngle(-38_deg);
  driveToPoint(Point{24_in, 0_in, 0_deg});
}
