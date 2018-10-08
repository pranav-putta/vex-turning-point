#include "robot.h"

using namespace std;

namespace robot {
  // Core class definition

  Core::Core() {
    // Initialize all members
    driveController = make_unique<controller::DriveController>(
      controller::DriveController(MTR_PORT_TOP_LEFT, MTR_PORT_TOP_RIGHT, MTR_PORT_BACK_LEFT,
        MTR_PORT_BACK_RIGHT, SIZE_WHEEL_RADIUS, SIZE_BASE_WIDTH));
    liftController = make_unique<controller::LiftController>(controller::LiftController(MTR_PORT_LIFT_1, MTR_PORT_LIFT_2));
    clawController = make_unique<controller::ClawController>(controller::ClawController(MTR_PORT_CLAW));
    launcherController = make_unique<controller::LauncherController>(controller::LauncherController(MTR_PORT_LAUNCHER));
  }

  // TODO: implement all of these
  void Core::updatePosition() {

  }

  void Core::moveTo(util::Position newPos) {

  }

  void Core::launchAutoAlign(util::Flag target) {

  }

  void Core::launch(double speed) {

  }

  void Core::placeOnPost(util::Post target) {

  }

  void Core::flipCap() {

  }

  void Core::changeLiftPosition() {

  }

  void Core::executeRemoteInput(int input[]) {

  }
}
