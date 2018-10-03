#ifndef BCI_MOTORCONTROL_C_INCLUDED
#define BCI_MOTORCONTROL_C_INCLUDED

#include "motorControl.h"

//Array for motors
static pros::Motor driveMotors[MOTOR_NUM];

/*
* Adds and initializes a motor (by name) to the motor array
*/
pros::Motor* addMotor(const int index, float slewRate)
{
	//Grab a spot in the motor array which
	//corresponds with which port the
	//physical motor is plugged into
	pros::Motor *m = &(driveMotors[index]);

	return m;
}

#endif //BCI_MOTORCONTROL_C_INCLUDED
