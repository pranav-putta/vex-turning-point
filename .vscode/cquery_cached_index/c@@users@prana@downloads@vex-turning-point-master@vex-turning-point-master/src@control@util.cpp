#include "util.h"

int util::convertSpeedToVoltage(float speed) {
  // Convert from m/s to rotatations/min
  double w = (speed * 30) * DRIVE_GEAR_RATIO / (M_PI * DRIVE_WHEEL_RADIUS);
  // Convert rotations/min to clicks per rotation
  w *= DRIVE_ENCODER_CLICKS_PER_ROTATION;

  // Use regression model to predict voltage required
  double voltage = w * DRIVE_VOLTAGE_REGRESSION_B0;
  voltage += DRIVE_VOLTAGE_REGRESSION_B1;

  return voltage;
}

float util::convertDistanceToEncoder(float distance) {
  float rotations = distance / (2 * M_PI * DRIVE_WHEEL_RADIUS);
  return rotations * DRIVE_ENCODER_CLICKS_PER_ROTATION;
}

std::pair<float, float> util::calculateVoltageCoefficient(pros::Motor lb, pros::Motor lf, pros::Motor rb, pros::Motor rf) {
  // Capture voltage vs. (average rpm over 50ms)
  int dataSize = 128;
  float vals[dataSize];
  vals[0] = 0;

  for (int v = 1; v <= 127; v++) {
      lb.move(v);
      lf.move(v);
      rb.move(v * (-1));
      rf.move(v * (-1));

      // Find average angular velocity in time interval of 50ms
      double velocity[40];
      double avgRotationalVelocity;
      for (int i = 0; i < 10; i ++) {
        avgRotationalVelocity += lb.get_actual_velocity();
        avgRotationalVelocity += lf.get_actual_velocity();
        avgRotationalVelocity += rb.get_actual_velocity();
        avgRotationalVelocity += rf.get_actual_velocity();
        pros::delay(5);
      }

      // Calculate average rotational velocity for that
      avgRotationalVelocity /= 40;

      // Assign pair value
      vals[v] = avgRotationalVelocity;
  }

  float x[dataSize];
  for (int i = 0; i < dataSize; i++) {
    x[i] = i;
  }

  return calculateRegressionLine(x, vals, dataSize);
}

std::pair<float, float> util::calculateRegressionLine(float *x, float *y, int dataSize) {

    // Arbitrary values needed to calculate regression
    double sumX = 0;
    double sumY = 0;
    double sumXY = 0;
    double sumXX = 0;
    double sumRES = 0;
    double res = 0;
    double b1 = 0;
    double b0 = 0;
    double sumYRES = 0;
    double meanY = 0;
    double meanX = 0;
    double resY = 0;
    double Rsqr = 0;

    // Calculate values
    for (int i = 0; i < dataSize; i++) {
      sumX += *(x + i);
      sumY += *(y + i);
      sumXY += *(x + i) * *(y + i);
      sumXX += *(x + i) * *(x + i);
    }

    // Calculate means of x and y
    meanX = sumX / dataSize;
    meanY = sumY / dataSize;

    // calculate slope
    b1 = (dataSize * sumXY - sumX * sumY) / (dataSize * sumXX - sumX * sumX);
    b0 = meanY - b1 * meanX;

    // calculate squared residuals
    for (int i = 0; i < dataSize; i++) {
      resY = pow(*(y + i) - b0 - (b1 * *(x + i)), 2);
      sumYRES += resY;
    }

    Rsqr = (sumRES - sumYRES) / sumRES;

    return std::pair<float, float>(b1, b0);
}
