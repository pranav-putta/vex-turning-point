#include "controller.h"
using namespace std;

namespace robot::controller {

  // Driver controller class definition

  DriveController::DriveController(int portTL_, int portTR_, int portBL_, int portBR_, double wheelSize, double baseSize) {
    // Initialize port definitions
    portTL = portTL_;
    portTR = portTR_;
    portBL = portBL_;
    portBR = portBR_;

    // Create chassis
    auto chassis = okapi::ChassisControllerFactory::create(
      {portTL, portBL}, // Left motors
      {portTR, portBR}, // Right motors
      okapi::AbstractMotor::gearset::red, // torque gearset
      {wheelSize, baseSize} // wheel radius, base width
    );
    chassisController = make_unique<okapi::AsyncMotionProfileController>(
      okapi::AsyncControllerFactory::motionProfile(1.0, 2.0, 10.0, chassis));

  }

  // TODO: Implement
  void DriveController::moveLinear(float dist, float speed) {

  }

  // Lift Controller class definition
  //TODO: Finish implementation of this, finish initialization of controller
  LiftController::LiftController(int port1_, int port2_) {
    port1 = port1_;
    port2 = port2_;
  }

  // Claw Controller class definition
  // TODO: Finish implementation of this, same as above
  ClawController::ClawController(int port_) {
    port = port_;
  }

  // Launcher Controller class definition
  // TODO: Finish implementation of this, same as above
  LauncherController::LauncherController(int port_) {
    port = port_;
  }

}
