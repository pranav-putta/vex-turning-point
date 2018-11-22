#ifndef PIDNN_CONTROLLER_H_
#define PIDNN_CONTROLLER_H_

#include <math.h>
#include <matrix.h>

// Structure that holds PID neural net values
typedef struct PIDNN {

  // nueral net weights and bias
  matrix** weights;
  matrix* biases;

  // variables to keep track of PID errors
  float targetValue;
  float error;
  float previousError;
  float integral;
  float derivative;
  float integralLimit;

} PIDNN;

// Initialize PIDNN structure controller to initial values
void PIDNNInit(struct PIDNN *controller, matrix* weights, matrix* biases);

// Computes the response v(t) value adjusted by the PIDNN controller
float PIDNNCompute(struct PIDNN *controller, float error);

// Tunes the PID Controller by running the back propogation algorithm
void PIDNNBackPropogate(struct PIDNN *controller);

void PIDNNSetTargetValue(struct PIDNN *controller, float targetValue);

#endif
