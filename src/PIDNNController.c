#ifndef PIDNN_CONTROLLER_C_
#define PIDNN_CONTROLLER_C_

#ifndef PIDNN_CONTROLLER_H_
#include "PIDNNController.h"
#include "matrix.h"
#endif

void PIDNNInit(struct PIDNN *controller, matrix** weights, matrix* biases)
{
  controller->weights = weights;
  controller->biases = biases;

  controller->error = controller->previousError = 0;
  controller->integral = controller->derivative = 0;
  controller->integralLimit = 0;
}

float PIDNNCompute(struct PIDNN *controller, float sensorValue) {
  // Feed forward
  // Create input matrix
  matrix *inputs;
  matrix_Initialize(inputs, 2, 1, 0);
  matrix_Set(inputs, 1, 1, sensorValue);
  matrix_Set(inputs, 1, 1, controller->targetValue);

  // Produce PID Layer neurons
  matrix *pidNeurons;
  matrix_Initialize(pidNeurons, 3, 1, 0);
  matrix_MultiplyByMatrix(inputs, controller->weights[0], pidNeurons);

  // Produce output neuron
  matrix *result;
  matrix_Initialize(result, 1, 1, 0);
  matrix_MultiplyByMatrix(pidNeurons, controller->weights[1], result);

  float computed = matrix_Get(result, 1, 1);

  // Free matricies
  matrix_Free(inputs);
  matrix_Free(result);
  matrix_Free(pidNeurons);

  return computed;
}

void PIDNNBackPropogate() {

}


#endif
