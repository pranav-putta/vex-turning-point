#include "setup.hpp"

void opcontrol() {

  while (true) {
    arcade();
    macros();
    lock();
    pros::delay(10);
  }
}
