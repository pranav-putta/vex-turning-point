/** @file init.c
 * @brief File for initialization code
 *
 * This file should contain the user initialize() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "init.h"

#define ENC_TOP_DRIVE_LEFT 2
#define ENC_BOT_DRIVE_LEFT 3
#define ENC_TOP_DRIVE_RIGHT 4
#define ENC_BOT_DRIVE_RIGHT 5

#define LEFT_ARROW  247
#define RIGHT_ARROW 246
#define MAX_AUTON 4
static  char select_str[16] = { LEFT_ARROW,  LEFT_ARROW,  LEFT_ARROW,  0, 0, 0, 0,
  'G', 'O', 0, 0, 0, 0, RIGHT_ARROW, RIGHT_ARROW, RIGHT_ARROW};

/*
 * Runs pre-initialization code. This function will be started in kernel mode one time while the
 * VEX Cortex is starting up. As the scheduler is still paused, most API functions will fail.
 *
 * The purpose of this function is solely to set the default pin modes (pinMode()) and port
 * states (digitalWrite()) of limit switches, push buttons, and solenoids. It can also safely
 * configure a UART port (usartOpen()) but cannot set up an LCD (lcdInit()).
 */
void initializeIO() {
}

/*
 * Runs user initialization code. This function will be started in its own task with the default
 * priority and stack size once when the robot is starting up. It is possible that the VEXnet
 * communication link may not be fully established at this time, so reading from the VEX
 * Joystick may fail.
 *
 * This function should initialize most sensors (gyro, encoders, ultrasonics), LCDs, global
 * variables, and IMEs.
 *
 * This function must exit relatively promptly, or the operatorControl() and autonomous() tasks
 * will not start. An autonomous mode selection menu like the pre_auton() in other environments
 * can be implemented in this task if desired.
 */
void initialize() {
  initSensors();
  initLCD();

  auton = 1;
  while (!isEnabled()) {
    autonSelect();
    delay(5);
  }

}

void autonSelect() {
  lcdPrint(uart1, 1, "Auton %d", auton);

  int btn = lcdReadButtons(uart1);
  switch (btn) {
    case LCD_BTN_LEFT:
      if (auton > 1) {
        auton--;
      }
      return;
    case LCD_BTN_RIGHT:
      if (auton < MAX_AUTON) {
        auton++;
      }
      return;
  }
}

void initLCD() {
  // Initialize LCD
  lcdInit(uart1);
  lcdClear(uart1);
  lcdSetBacklight(uart1, true);

  // Start auton select
  lcdSetText(uart1, 1, "Initializing...");
  lcdSetText(uart1, 2, select_str);
}

void initSensors() {
  // Initialize encoders
  driveLEnc = encoderInit(ENC_TOP_DRIVE_LEFT, ENC_BOT_DRIVE_LEFT, false);
  driveREnc = encoderInit(ENC_TOP_DRIVE_RIGHT, ENC_BOT_DRIVE_RIGHT, true);
}
