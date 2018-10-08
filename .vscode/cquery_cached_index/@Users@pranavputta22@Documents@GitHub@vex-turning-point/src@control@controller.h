#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "main.h"

using namespace std;

// Controller namespace
namespace robot::controller {

  // Base controller class
  class Controller {};

  // Controller class for Chassis
  class DriveController : Controller {
  public:
    /**
     * Default motion controller constructor, initializes with pointer to chasis controller
     */
    DriveController(int portTL_, int portTR_, int portBL_, int portBR_, double wheelSize_, double baseSize_);
  private:
    // Internal chassis controller
    unique_ptr<okapi::AsyncMotionProfileController> chassisController;

    // Motor Ports
    int portTL;
    int portTR;
    int portBL;
    int portBR;

    /**
     * Moves the robot linearly, backwards or forward
     * @param dist  [distance to travel in meters]
     * @param speed [speed to travel at in meters per second]
     */
    void moveLinear(float dist, float speed);
  };

  // Controller Class for Lift
  class LiftController : Controller {
  public:
    /**
     * Default constructor, initializes motor port and internal controller
     * @param port [motor port]
     */
    LiftController(int port1, int port2);
  private:
    // Internal controller
    unique_ptr<okapi::AsyncPosPIDController> motor1Control;
    unique_ptr<okapi::AsyncPosPIDController> motor2Control;

    // Lift ports of motor 1 and 2
    int port1;
    int port2;
  };

  // Controller class for Claw
  class ClawController : Controller {
  public:
    /**
     * Default constructor, initializes motor port and internal controller
     * @param port [motor port]
     */
    ClawController(int port);
  private:
    // Internal Controller
    unique_ptr<okapi::AsyncPosPIDController> clawControl;

    // Claw motor port
    int port;
  };

  // Controller class for Launcher
  class LauncherController : Controller {
  public:
    /**
     * Default constructor, intializes motor port and internal controller
     * @param port [flywheel motor port]
     */
    LauncherController(int port);
  private:
    //Internal Controller
    unique_ptr<okapi::AsyncPosPIDController> flyWheelControl;

    // Flywheel motor port
    int port;
  };

}

#endif
