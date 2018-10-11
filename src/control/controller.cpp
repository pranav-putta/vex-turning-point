#include "controller.h"
using namespace std;
using namespace okapi;

namespace robot::controller {

  // Driver controller class definition

  DriveController::DriveController(int8_t portTL_, int8_t portTR_, int8_t portBL_, int8_t portBR_, double wheelSize, double baseSize) {
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
    chassisController = &chassis;

    auto profiler = okapi::AsyncControllerFactory::motionProfile(1.0, 2.0, 10.0, *chassisController);
    chassisMotionProfiler = &profiler;
  }

  // TODO: Implement
  void DriveController::moveLinear(float dist, float speed) {

  }

  void DriveController::moveOnPath(vector<okapi::Point> path) {
    // TODO: convert path to an initializer list
    chassisMotionProfiler->generatePath({
      okapi::Point{0_ft, 0_ft, 0_deg}}, "Path motion");
    chassisMotionProfiler->setTarget("Path motion");
    chassisMotionProfiler->waitUntilSettled();
  }

  //TODO: implement
  void DriveController::pointTurn(okapi::QAngle angle) {

  }

  void DriveController::tankDrive(pros::Controller &controller) {
    chassisController->tank(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),
                            -controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
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
