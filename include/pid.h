/*
* This file is responsible for updating PID values for motors and sensors
* It tunes the PID values using training of a neural network
*/
#include "main.h"
#include "controller.h"

// STRUCTURE DEFINITIONS
typedef struct PIDAttrs {
  double kP, kI, kD;
} PID;

typedef struct NeuralNetworkAttrs {
  double weight[1000];
  double biases[1000];
} NeuralNet;

// PID FUNCTIONS
void updatePID(PID *pid);

// NN FUNCTIONS
void trainPID(PID *pid, NeuralNet *nn);
