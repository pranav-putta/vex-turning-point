#include "robot.h"

// Drive robot forward or backwards a certain distance -- using motion control profiles to track robot nav
void drive(struct MotionProfile *profile, float targetDistance) {
  // initialize motion profiler with distance
  MotionProfileEasyParams(profile, MAX_ACCEL, MAX_VEL, targetDistance);

  float time = 0;
  float dt = 0.02;

  PID pid;
  PIDInit(&pid, PID_DRIVE_KP, PID_DRIVE_KI, PID_DRIVE_KD);

  float dist = 0;
  float actualDist = 0;

  while(!MotionProfileIsComplete(profile, time)) {
    float velocity = MotionProfileCompute(profile, time);
    dist += velocity * dt;
    actualDist = ((encoderGet(driveLEnc) + encoderGet(driveREnc)) / (360 * 2)) * 2 * 3.1415 * WHEEL_RADIUS;

    float motorSpeed = 127 * velocity + PIDCompute(&pid, (dist - actualDist));
    motorSet(MTR_L, motorSpeed);
    motorSet(MTR_R, motorSpeed);
    time += dt;

    delay(20);
  }

  // Double check and PID the error
  while (fabs(dist - actualDist) > MAX_ERR) {
    actualDist = ((encoderGet(driveLEnc) + encoderGet(driveREnc)) / (360 * 2)) * 2 * 3.1415 * WHEEL_RADIUS;
    float err = dist - actualDist;

    float motorSpeed = 127 * PIDCompute(&pid, err);
    motorSet(MTR_L, motorSpeed);
    motorSet(MTR_R, motorSpeed);
    delay(20);
  }
}

void turnAngle(MotionProfile *profile, float degrees) {
  float targetDistance = degrees * (3.1415 / 180) * WHEELBASE_WIDTH;

  // initialize motion profiler with distance
  MotionProfileEasyParams(profile, MAX_ACCEL, MAX_VEL, targetDistance);

  float time = 0;
  float dt = 0.02;

  PID pid;
  PIDInit(&pid, PID_DRIVE_KP, PID_DRIVE_KI, PID_DRIVE_KD);

  float dist = 0;
  float actualDist = 0;

  while(!MotionProfileIsComplete(profile, time)) {
    float velocity = MotionProfileCompute(profile, time);
    dist += velocity * dt;
    actualDist = ((encoderGet(driveLEnc) - encoderGet(driveREnc)) / (360 * 2)) * 2 * 3.1415 * WHEEL_RADIUS;

    float motorSpeed = 127 * velocity + PIDCompute(&pid, (dist - actualDist));
    motorSet(MTR_L, motorSpeed);
    motorSet(MTR_R, -motorSpeed);
    time += dt;

    delay(20);
  }

  // Double check and PID the error
  while (fabs(dist - actualDist) > MAX_ERR) {
    actualDist = ((encoderGet(driveLEnc) + encoderGet(driveREnc)) / (360 * 2)) * 2 * 3.1415 * WHEEL_RADIUS;
    float err = dist - actualDist;

    float motorSpeed = 127 * PIDCompute(&pid, err);
    motorSet(MTR_L, motorSpeed);
    motorSet(MTR_R, -motorSpeed);
    delay(20);
  }
}

void launchBall(Flag flag) {
  // Roll back intakes a little
  setIntake(false);

  // Start flywheel, wait until target speed is achieved

  // Let ball free
  setIntake(true);
  delay(50);
}
