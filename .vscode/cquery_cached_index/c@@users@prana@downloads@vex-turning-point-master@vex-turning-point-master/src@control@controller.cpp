#include "controller.h"

// Controller Implementation

Controller::Controller() {
  initializeMotors();
}

void Controller::initializeMotors() {
  // Add left back motor
  addMotor(MTR_PORT_LEFT_BACK, MTR_ID_LEFT_BACK, DRIVE);
  // Add left front motor
  addMotor(MTR_PORT_LEFT_FRONT, MTR_ID_LEFT_FRONT, DRIVE);
  // Add right back motors
  addMotor(MTR_PORT_RIGHT_BACK, MTR_ID_RIGHT_BACK, DRIVE);
  // Add right front motor
  addMotor(MTR_PORT_RIGHT_FRONT, MTR_ID_RIGHT_FRONT, DRIVE);
}

void Controller::addMotor(int port, std::string id, MotorType type) {
  motors[id] = Motor();
}

void Controller::linearMotionDrive(float distance, float speed, Direction direction) {
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
