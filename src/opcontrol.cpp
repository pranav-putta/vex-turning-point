#include "opcontrol.hpp"

using namespace robot;

void opcontrol() {
  pros::Controller master(pros::E_CONTROLLER_MASTER);
  robot::controller* c = robot::initializeController();

  while (true) {
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			auton1(*c);
		}
    pros::delay(20);
  }
}

void auton1(robot::controller &c) {
  c.setRollerState(FORWARD);
  c.driveToPosition(location(SQ * 2.5, 0_in, 0_deg));
  c.setRollerState(INACTIVE);
  c.turn(90_deg);
  c.driveToPosition(location(0_in, SQ * 2.5, 0_deg));
  c.resetPuncher();
  c.driveToPosition(location(0_in, SQ, 0_deg));
  c.firePuncher();
  c.turn(180_deg);
  c.driveToPosition(location(SQ, SQ, 0_deg));
  c.driveOnPlatform();
}

void auton2(robot::controller &c) {}

void auton3(robot::controller &c) {}

void auton4(robot::controller &c) {}
