#include "main.h"
#include "pid.h"

// COMMANDS

/* Drives robot forward
*
* distance -- distance in (cm) to travel
* wait -- time in (ms) to wait
*/
void drive(double distance, unsigned int wait);

void turn(double angle, unsigned int wait, int speed);
