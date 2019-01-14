#include "main.h"
#include "math.h"
#include "stdio.h"

using namespace okapi;
using namespace std;

typedef std::pair<int, int> point;

#define MOTOR_TL 1_mtr
#define MOTOR_TR 2_mtr
#define MOTOR_BL 3_mtr
#define MOTOR_BR 4_mtr
#define MOTOR_LIFT 5_mtr
#define MOTOR_PUNCHER 6_mtr
#define MOTOR_CLAW 7_mtr
#define MOTOR_INTAKE 8_mtr

#define BASE_SIZE 17.5_in
#define WHEEL_SIZE 4_in

#define SQ 23.416_in
#define REV 900

#define LIFT_HEIGHT_LOW 200
#define LIFT_HEIGHT_MID 900
#define LIFT_HEIGHT_HIGH 2000

namespace robot {

struct location {
  QLength x, y;
  QAngle theta;

  location(QLength x = 0_in, QLength y = 0_in, QAngle theta = 0_deg)
      : x(x), y(y), theta(theta) {}

  location operator+(const location &a) {
    return location(a.x + x, a.y + y, a.theta + theta);
  }

  location operator-(const location &a) {
    return location(x - a.x, y - a.y, theta - a.theta);
  }

  // error
  double operator%(const location &a) {
    return std::pow(((a.x - x) + (a.y - y)).getValue(), 2);
  }

  // reset
  void operator<<(int corner) {
    if (corner == 1) {
      x = -3.5 * SQ;
      y = 0_in;
      theta = 90_deg;
    } else if (corner == 2) {
      x = -3.5 * SQ;
      y = 6 * SQ;
      theta = 90_deg;
    } else if (corner == 3) {
      x = 2.5 * SQ;
      y = 6 * SQ;
      theta = 90_deg;
    } else if (corner == 4) {
      x = 2.5 * SQ;
      y = 0_in;
      theta = 90_deg;
    }
  }

  // rotate axis
  void operator>>(double degrees) {
    degrees = d2r(-degrees);

    x = (x * std::cos(degrees)) + (y * std::sin(degrees));
    y = -(x * std::sin(degrees)) + (y * std::cos(degrees));
    theta = 0_deg;
  }
};

struct odometryData {
  long tl, tr, bl, br;

  odometryData(long tl = 0, long tr = 0, long bl = 0, long br = 0)
      : tl(tl), tr(tr), bl(bl), br(br) {}

  odometryData operator+(const odometryData &a) {
    return odometryData(tl + a.tl, tr + a.tr, bl + a.bl, br + a.br);
  }

  odometryData operator-(const odometryData &a) {
    return odometryData(tl - a.tl, tr - a.tr, bl - a.bl, br - a.br);
  }
};

enum LiftState { TOP, MIDDLE, BOTTOM };

enum RollerState { FORWARD, BACKWARD, INACTIVE };

class odometry {
private:
  // point current
  odometryData last;

  // Retrieve position value of nth motor
  long getEncoderVal(int motor);

public:
  odometry() {}
  // update odometry data
  location updateLocation(location current, Motor tl, Motor tr, Motor bl,
                          Motor br);
};

class controller {
public:
  // Current and expected locations of bot
  location currentLoc;
  location expectedLoc;

  // Odometry Controller
  odometry odomControl;

  // OKAPI controllers
  Motor drive_TL = MOTOR_TL;
  Motor drive_TR = MOTOR_TR;
  Motor drive_BL = MOTOR_BL;
  Motor drive_BR = MOTOR_BR;
  Motor lift = MOTOR_LIFT;
  Motor claw = MOTOR_CLAW;
  Motor puncher = MOTOR_PUNCHER;
  Motor intake = MOTOR_INTAKE;

  ChassisControllerIntegrated chassis =
      ChassisControllerFactory::create({drive_TL, drive_BL},          // Left
                                       {drive_TR, drive_BR},          // Right
                                       AbstractMotor::gearset::green, // Gears
                                       {WHEEL_SIZE, BASE_SIZE});      // Base

  AsyncMotionProfileController motionProfiler =
      AsyncControllerFactory::motionProfile(1.0, 2.0, 5.0, chassis);

  AsyncPosPIDController liftController =
      AsyncControllerFactory::posPID(lift, 0, 0, 0);

  AsyncPosIntegratedController clawController =
      AsyncControllerFactory::posIntegrated(lift);

  // Retrieve current position of robot as a pair
  location getCurrentPosition();

  // Default constructor
  controller() {}

  // Drive robot to indicated position based on current odometry data
  double driveToPosition(location pt);

  // Drive until platform reached
  void driveOnPlatform();

  void turn(QAngle angle);

  // Zero robot position (left hand corner)
  void resetPosition(int corner);

  // Correct position with PID values
  void correctPosition(location pos);

  // Move lift to predefined location
  void setLiftState(LiftState state);

  // Change Roller state
  void setRollerState(RollerState state);

  // Turn claw 180 degrees
  void flipCap();

  // Reset puncher by pulling back
  bool resetPuncher();

  // Fire puncher
  bool firePuncher();

  // updates odometry data
  void update();
};

// initializer
controller *initializeController();

} // namespace robot
