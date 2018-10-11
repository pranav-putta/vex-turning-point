#include "main.h"
#include "control/robot.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

	// 1. Calculate voltage coefficients
	// 2. Calculate gear ratio, wheel radius, and encoder clicks per rotations
	// 3. drive and test if velocity is maintained and distance is solid
  pros::Controller master(pros::E_CONTROLLER_MASTER);
  robot::Core core = robot::Core();

  while(true) {
    core.tankDrive(master);
    core.updatePosition();

    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      okapi::Point *p = core.getCurrentPosition();
      int x = (int) p->x.getValue();
      int y = (int) p->y.getValue();
      int theta = (int) p->theta.getValue();

      master.set_text(1, 1, "Captured");
      pros::lcd::set_text(1, "x: " + to_string(x));
      pros::lcd::set_text(2, "y: " + to_string(y));
      pros::lcd::set_text(3, "theta: " + to_string(theta));

    }

    pros::delay(20);
  }
}

void autonomousTest() {

}
