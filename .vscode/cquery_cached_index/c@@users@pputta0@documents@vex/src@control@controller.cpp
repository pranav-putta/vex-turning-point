#include "controller.h"
#include "util.cpp"


/**
*   Drive definition
*/
void Controller::linearMotionDrive(float units, float speed, Direction direction ) {
  int voltage = util::convertSpeedToVoltage(speed);
  Motor lb = motors[MTR_ID_LEFT_BACK];
  Motor lf = motors[MTR_ID_LEFT_FRONT];
  Motor rb = motors[MTR_ID_RIGHT_BACK];
  Motor rf = motors[MTR_ID_RIGHT_FRONT];

  (*lb.motor).move_voltage(voltage);
  (*lf.motor).move_voltage(voltage);
  (*rb.motor).move_voltage(-1 * voltage);
  (*rf.motor).move_voltage(-1 * voltage);
};
