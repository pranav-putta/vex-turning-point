#ifndef  UTIL_H_
#define UTIL_H_

#include "main.h"
#include "time.h"
#include <vector>
#include <map>
#include <math.h>

// Constants
#define DRIVE_WHEEL_RADIUS 3.2
// Motor gear to wheel gear
#define DRIVE_GEAR_RATIO 4
#define DRIVE_ENCODER_CLICKS_PER_ROTATION 600;
// Voltage coefficient
#define DRIVE_VOLTAGE_REGRESSION_B0 2;
#define DRIVE_VOLTAGE_REGRESSION_B1 1.2;

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


class util {
public:
  /**
   * Converts speed in meters/sec to voltage for motor usage. Takes into account
   * gear ratio to determine necessary revolutions/sec
   * @method util::convertSpeedToVoltage
   * @param  speed                       [desired speed in (m/s)]
   * @return                             [voltage between [-127, 127]]
   */
  static int convertSpeedToVoltage(float speed);

  /**
   * Use experimental test to find the slope of voltage vs rpm relationship
   * @method calculateVoltageCoefficient
   * @param  lb                          [description]
   * @param  lf                          [description]
   * @param  rb                          [description]
   * @param  rf                          [description]
   * @return                             [description]
   */
  static std::pair<float, float> calculateVoltageCoefficient(pros::Motor lb, pros::Motor lf, pros::Motor rb, pros::Motor rf);

  /**
   * Calculates regression line for given data, pair<m, b>
   * y = mx + b
   * @method calculateRegressionLine
   * @param  x                       [description]
   * @param  y                       [description]
   */
  static std::pair<float, float> calculateRegressionLine(float x[], float y[], int dataSize);
};
#endif
