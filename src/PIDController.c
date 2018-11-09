#ifndef __BNS_PID_CONTROLLER_C
#define __BNS_PID_CONTROLLER_C

#ifndef __BNS_PID_CONTROLLER_H
#include "PIDController.h"
#endif

// Initializes the default values for the PID Controller
void PIDInit(struct PID *controller, float kP, float kI, float kD)
{
    controller->kP = kP;
    controller->kI = kI;
    controller->kD = kD;

    controller->error = controller->previousError = 0;
    controller->integral = controller->derivative = 0;

    controller->kILimit = 50;
}

// Computes the response for the PID controller
float PIDCompute(struct PID *controller, float error)
{
    controller->error = error;
    controller->integral += error;
    controller->derivative = error - controller->previousError;
    controller->previousError = error;

    if(controller->integral > controller->kILimit)
        controller->integral = controller->kILimit;

    if(controller->integral < -controller->kILimit)
        controller->integral = -controller->kILimit;

    return controller->kP * controller->error
                + controller->kI * controller->integral
                + controller->kD * controller->derivative;
}

// Sets the limit for the integral constant
void PIDSetIntegralLimit(struct PID *controller, float kILimit)
{
    controller->kILimit = kILimit;
}

// Restes the integral value
void PIDResetIntegral(struct PID *controller)
{
    controller->integral = 0;
}

#endif
