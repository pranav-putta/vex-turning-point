#include "util.h"

float sigmoid(float z) {
  return (2 / (1 + pow(CONST_E, z))) - 1;
}
