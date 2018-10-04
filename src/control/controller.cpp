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
  motors[id] = Motor(port, type);
}

void Controller::linearMotionDrive(float distance, float speed, Direction direction) {
  // Determine voltage and encoder conversions
  int voltage = util::convertSpeedToVoltage(speed);
  double targetEnc = (distance / speed) * 1000;

  // Assign motor values
  Motor lb = motors[MTR_ID_LEFT_BACK];
  Motor lf = motors[MTR_ID_LEFT_FRONT];
  Motor rb = motors[MTR_ID_RIGHT_BACK];
  Motor rf = motors[MTR_ID_RIGHT_FRONT];

  // Move robot with target speed voltage
  (lb.getMtr()).move(voltage);
  (lf.getMtr()).move(voltage);
  (rb.getMtr()).move(-1 * voltage);
  (rf.getMtr()).move(-1 * voltage);

  // Move until target distance reached
  float avgEnc = 0;
  while (avgEnc < targetEnc) {
    avgEnc = lb.getMtr().get_position();
    avgEnc += lf.getMtr().get_position();
    avgEnc += rb.getMtr().get_position();
    avgEnc += rf.getMtr().get_position();

    avgEnc /= 4;
  }

  // Stop moving
  lb.getMtr().move(0);
  lf.getMtr().move(0);
  rb.getMtr().move(0);
  rf.getMtr().move(0);


  // Move robot with target speed voltage
  /* double w = (speed * 30) * DRIVE_GEAR_RATIO / (M_PI * DRIVE_WHEEL_RADIUS);
     w *= DRIVE_ENCODER_CLICKS_PER_ROTATION;

     lb.getMtr().move_relative(targetEnc, w)*/

};
