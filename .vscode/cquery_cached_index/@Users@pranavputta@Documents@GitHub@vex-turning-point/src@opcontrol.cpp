#include "robot.hpp"

void opcontrol() {
  initializeOpControl();

  while (true) {
    arcade();
    master_macros();
    nigga_macros();
    lock();
    pros::delay(10);
  }
}

/**
 * Setup robot for driver control
 */
// TODO: Identify lift speed presets
void initializeOpControl() {
  // Initialize all motors to init settings
  is_tl_reversed = false;
  is_bl_reversed = false;
  is_tr_reversed = true;
  is_br_reversed = true;
  mtr_dr_tl.setReversed(is_tl_reversed);
  mtr_dr_tr.setReversed(is_tr_reversed);
  mtr_dr_br.setReversed(is_br_reversed);
  mtr_dr_bl.setReversed(is_bl_reversed);

  chassis.setMaxVelocity(200);

  double currentClawPos = mtr_claw.getPosition();
  clawLock = CURRENT;
  liftLock = FREE;
  liftState = LiftState::FOLDED;

  k_speed_lift = 0.4;
}

/**
 * Arcade control
 * Needs to be run iteratively
 */
void arcade() {
  forward =
      master.getAnalog(ControllerAnalog::leftY) * direction * k_speed_forward;
  yaw = master.getAnalog(ControllerAnalog::rightX) * k_speed_yaw;

  mtr_dr_tl.move(forward + yaw);
  mtr_dr_tr.move(forward - yaw);
  mtr_dr_bl.move(forward + yaw);
  mtr_dr_br.move(forward - yaw);
}

/**
 * Master macro controls
 */
void master_macros() {
  /* Master controls */

  // Lift Macros
  if (unfoldLiftButton.changedToPressed()) {
    pullUpLift();
  }

  if (descoreButton.changedToPressed()) {
    descore();
  }

  // Intake Macros
  if (intakeStateButton.changedToReleased()) {
    if (intakeState == FORWARD || intakeState == BACKWARD) {
      intakeState = IntakeState::IDLE;
    } else {
      intakeState = IntakeState::FORWARD;
    }

    setIntakeState(intakeState);
  }

  // Lift Control
  // Lift up if button is pressed
  if (liftUpButton.isPressed()) {
    liftLock = LockState::FREE;
    mtr_lift.move(127 * k_speed_lift);
  }
  // Lift down if button is pressed
  else if (liftDownButton.isPressed()) {
    liftLock = LockState::FREE;
    mtr_lift.move(-127 * k_speed_lift);
  }
  // Lock lift if buttons were released & set speed to 0
  else if (liftUpButton.changedToReleased() ||
           liftDownButton.changedToReleased()) {
    liftLock = LockState::CURRENT;
    mtr_lift.move(0);
  }

  // Lift presets
  // TOP
  if (liftPresetHighButton.changedToPressed()) {
    setLiftState(LiftState::TOP);
  }
  // MIDDLE
  else if (liftPresetMidButton.changedToPressed()) {
    setLiftState(LiftState::MIDDLE);
  }
  // BOTTOM
  else if (liftPresetGroundButton.changedToPressed()) {
    setLiftState(LiftState::GROUND);
  }
  // SLIGHTLY UP
  else if (liftPresetRestButton.changedToPressed()) {
    setLiftState(LiftState::FOLDED);
  }

  // Flip Cap
  if (clawFlipButton.changedToPressed()) {
    flipCap();
  }
}

void nigga_macros() {
  /* Slave Controls */

  //  Reverse drive
  if (reverseButton.changedToPressed()) {
    direction = -direction;
  }

  // Change Speeds
  // Regular speed
  if (regularSpeedButton.changedToPressed()) {
    setConstants(1, 0.8, 0.6);
    master.setText(1, 1, "REG SPD");
  }
  // Holding Cap speed
  else if (holdingSpeedButton.changedToPressed()) {
    setConstants(0.75, 0.75, 0.5);
    master.setText(1, 1, "CAP SPD");
  }
  // Goal post speed
  else if (goalPostSpeedButton.changedToPressed()) {
    setConstants(0.5, 0.25, 0.25);
    master.setText(1, 1, "GOAL SPD");
  }

  // Descore Autonomous
  if (descoreButton.changedToPressed()) {
    descore();
  }
}
