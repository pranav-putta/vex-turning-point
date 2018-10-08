#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "util.h"

// Motor ID definitions
#define MTR_ID_LEFT_BACK "left_back"
#define MTR_ID_LEFT_FRONT "left_front"
#define MTR_ID_RIGHT_BACK "right_back"
#define MTR_ID_RIGHT_FRONT "right_front"

// Motor port definitions
#define MTR_PORT_LEFT_BACK 10
#define MTR_PORT_RIGHT_BACK 1
#define MTR_PORT_LEFT_FRONT 20
#define MTR_PORT_RIGHT_FRONT 11

/* Controller definition */
class Controller {
public:
  // Variables
  std::map<std::string, Motor> motors;   // Holds motor port values

  /**
   * Default constructor for Controller class
   * @method Controller
   */
  Controller();

 /**
  * Move drive train in one dimention
  * @method linearMotionDrive
  * @param  units             [number of units to displace, measured in (meters)]
  * @param  speed             [speed in (m/s) for desired motion]
  * @param  d                 [vector direction to move in]
  */
  void linearMotionDrive(float displacement, float speed, Direction d);

 /**
  * Turns robot for desired degrees
  * @method angularMotionDrive
  * @param  angle              [desired angle to turn to, measure in (rad)]
  * @param  speed              [angular velocity of turn, measure in (rad/sec)]
  */
  void angularMotionDrive(float angle, float speed);

  void lift(float units, float speed);

  void clawTurn(float angle, float speed);

  /* Initialize motor map with values */
  void initializeMotors();

private:
  /**
   * Add motor to map
   * @method addMotor
   * @param  port     [Port of desired motor]
   * @param  id       [ID to call desired motor]
   * @param  type     [Type of motor in use]
   */
  void addMotor(int port, std::string id, MotorType type);
};

#endif
