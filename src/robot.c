#include "robot.h"

//
void drive(struct MotionProfile *profile, float distance) {
  // initialize motion profiler with distance
  MotionProfileEasyParams(profile, MAX_ACCEL, MAX_VEL, distance);

  float time = 0;
  float dt = 0.05;

  PID pid;
  PIDInit(&pid, 0,0,0);

  while(!MotionProfileIsComplete(profile, time)) {
    float velocity = MotionProfileCompute(profile, time);
    motorSet(MTR_L, velocity);
    time += dt;
  }
}

void turnAngle(float degrees) {

}
