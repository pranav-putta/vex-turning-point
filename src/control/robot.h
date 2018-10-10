#ifndef ROBOT_H_
#define ROBOT_H_

// Includes
#include "main.h"
#include "util.h"
#include "controller.h"

using namespace std;

// Robot Constants
#define MTR_PORT_TOP_LEFT 1
#define MTR_PORT_TOP_RIGHT 2
#define MTR_PORT_BACK_LEFT 3
#define MTR_PORT_BACK_RIGHT 4
#define MTR_PORT_LIFT_1 5
#define MTR_PORT_LIFT_2 6
#define MTR_PORT_LAUNCHER 7
#define MTR_PORT_CLAW 8

#define SIZE_WHEEL_RADIUS 2
#define SIZE_BASE_WIDTH 12.5

// Prototype for robot namespace
namespace robot {

  /**
   * Core class used to access robot and its functions,
   * including movement and data analytics
   */
  class Core {
  public:
    // Construction of Core
    Core();

    /**
     * Updates position of robot using odometry data
     */
    void updatePosition();

    /**
     * Creates a path for the robot to move to the new location
     * @param newPoint [Point to move to]
     */
    void moveTo(okapi::Point& newPoint);

    /**
     * Launches a ball to the specified flag, and auto aligns itself
     * @param flag      [the target flag]
     */
    void launchAutoAlign(util::Flag& target);

    /**
     * Launches a ball with the specified speed
     * @param speed [intial velocity of ball]
     */
    void launch(double& speed);

    /**
     * Places the cap on the specified post
     * @param target [type of post to place the cap]
     */
    void placeOnPost(util::Post& target);

    /**
     * Flips cap using claw
     */
    void flipCap();

    /**
     * Changes the position of lift
     */
    void changeLiftPosition();

    /**
     * Use for opcontrol
     * @param input [inputs from remote controller]
     */
    void executeRemoteInput(int input[]);


  private:
    // Controller for drive
    unique_ptr<controller::DriveController> driveController;

    // Controller for lift
    unique_ptr<controller::LiftController> liftController;

    // Controller for claw
    unique_ptr<controller::ClawController> clawController;

    // Controller for Launcher
    unique_ptr<controller::LauncherController> launcherController;

    // Position manager to keep track of location of robot
    unique_ptr<util::PositionManager> positionManager;

  };
}

#endif
