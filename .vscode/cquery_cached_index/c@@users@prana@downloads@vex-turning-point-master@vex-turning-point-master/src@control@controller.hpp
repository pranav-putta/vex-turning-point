#include "main.h"
#include <vector>
#include <map>

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

/*  Defines direction vector of Robot */
enum Direction {
  FORWARD,
  BACKWARD
};

/*  Defines type of motor being used */
enum MotorType {
  DRIVE, LIFT, CLAW
};

/* Motor definition */
struct Motor {

  int port;
  MotorType type;
  pros::Motor *motor;

};

/* Controller definition */
class Controller {
public:
  // Variables
  std::map<std::string, Motor> motors;   // Holds motor port values

  // Default constructor
  Controller() {
    // Initialize variables
    initializeMotors();
  }

  /* Move in forward or backward direction
  *  units - measure in meters
  *  speed - measured in meters/sec
  *  d - direction to move in {forward, backwards}
  *  Converts speed and units into rotations per second
  */
  void linearMotionDrive(float units, float speed, Direction d);

  /* Turn robot theta radians
  *  angle - measure in radians relative to initial angle
  *  speed - measure in radians/sec
  *  Converts speed and units into rotations per second of motor
  */
  void angularMotionDrive(float angle, float speed);

  void lift(float units, float speed);

  void clawTurn(float angle, float speed);

  /* Initialize motor map with values */
  void initializeMotors() {
    // Add left back motor
    addMotor(MTR_PORT_LEFT_BACK, MTR_ID_LEFT_BACK, DRIVE);
    // Add left front motor
    addMotor(MTR_PORT_LEFT_FRONT, MTR_ID_LEFT_FRONT, DRIVE);
    // Add right back motors
    addMotor(MTR_PORT_RIGHT_BACK, MTR_ID_RIGHT_BACK, DRIVE);
    // Add right front motor
    addMotor(MTR_PORT_RIGHT_FRONT, MTR_ID_RIGHT_FRONT, DRIVE);
  };

private:
  // Add motor definition
  void addMotor(int port, std::string id, MotorType type) {
    motors[id] = Motor();
  }
};
