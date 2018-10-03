#include "main.h"

using namespace std;

class Motor {
public:
  int arrIndex;
  pros::Motor mtr;
};

class DriveMotor: Motor {
public:
  int reqSpeed;   //Input speed
	float artSpeed; //Artificial speed (the exact speed as governed by the slew rate)
	float slew;     //Slew rate
	bool active;    //Whether or not to update this motor
};
