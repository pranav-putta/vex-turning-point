/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "auto.h"

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */
void autonomous() {
  MotionProfileInit(&autonMotionProfiler);

  switch (auton) {
    case 1:
      auton1();
      break;
  }
}

void auton1() {
  // ~2 seconds
  launchBall(FLAG_HIGH);

  // Flip cap and get ball
  turnAngle(-90);
  setIntake(true);
  drive(&autonMotionProfiler, 1.7);
  drive(&autonMotionProfiler, -1.7);

  // Hit bottom flag
  turnAngle(90);
  launchBall(FLAG_LOW);
  drive(&autonMotionProfiler, 2);
  drive(&autonMotionProfiler, -0.5);

  // Flip cap
  turnAngle(-90);
  drive(&autonMotionProfiler, 1.7);
  drive(&autonMotionProfiler, -0.5);

  // Get on platform
  turnAngle(-90);
  driveOntoPlatform(&autonMotionProfiler, 2);
}
