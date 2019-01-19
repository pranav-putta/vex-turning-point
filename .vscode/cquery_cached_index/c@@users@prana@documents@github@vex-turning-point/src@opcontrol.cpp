#include "robot.hpp"

void opcontrol() {
  initOpControl();

  while (true) {
    arcade();
    macros();
    lock();
    pros::delay(10);
  }
}
