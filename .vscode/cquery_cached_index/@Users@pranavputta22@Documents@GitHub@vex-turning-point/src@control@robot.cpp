#include "robot.h"

using namespace std;

namespace robot {
  // Core class definition

  Core::Core() {
    // Initialize all members
    driveController = make_unique<controller::DriveController>(
      controller::DriveController(MTR_PORT_TOP_LEFT, MTR_PORT_TOP_RIGHT, MTR_PORT_BACK_LEFT,
        MTR_PORT_BACK_RIGHT, SIZE_WHEEL_RADIUS, SIZE_BASE_WIDTH));
    liftController = make_unique<controller::LiftController>(MTR_PORT_LIFT_1, MTR_PORT_LIFT_2);
    clawController = make_unique<controller::ClawController>(MTR_PORT_CLAW);
    launcherController = make_unique<controller::LauncherController>(MTR_PORT_LAUNCHER);
    positionManager = make_unique<util::PositionManager>();
  }

  // TODO: implement all of these
  void Core::updatePosition() {

  }

  void Core::moveTo(okapi::Point& newPos) {
      // Generate a path to new position
      okapi::Point& current = positionManager->getCurrentPosition();
      initializer_list<okapi::Point> path = util::PathManager::instance().calculateShortestPath(current, newPos);

      driveController->moveOnPath(path);
  }

  void Core::launchAutoAlign(util::Flag& target) {
    okapi::Point& current = positionManager->getCurrentPosition();
    okapi::QAngle angle = util::PathManager::instance().calculateLaunchBaseAngle(current, target);
    okapi::QSpeed launchSpeed = util::PathManager::instance().calculateLaunchSpeed(current, target);

    okapi::QAngle deltaTheta = current.theta - angle;
  }

  void Core::launch(double& speed) {

  }

  void Core::placeOnPost(util::Post& target) {

  }

  void Core::flipCap() {

  }

  void Core::changeLiftPosition() {

  }

  void Core::executeRemoteInput(int input[]) {

  }
}
