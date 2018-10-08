#ifndef UTIL_H_
#define UTIL_H_

#include "main.h"
using namespace std;

// Utilities for robot namespace
namespace robot::util {

    /**
     * Flag positions
     */
    enum Flag {
      TOP_LEFT, MIDDLE_LEFT, BOTTOM_LEFT,
      TOP_CENTER, MIDDLE_CENTER, BOTTOM_CENTER,
      TOP_RIGHT, MIDDLE_RIGHT, BOTTOM_RIGHT
    };

    /**
     * Type of post
     */
    enum Post {
      TALL, SHORT
    };

    /**
     * Structure for position object
     * Stores (x, y) coordinate of robot and angle relative to start
     */
    struct Position {
      float x, y, theta;

      /**
       * Default position constructor, initializes all variables to 0
       */
      Position();

      /**
       * Create position object with initial values
       * @param x_     X coordinate
       * @param y_     Y coordinate
       * @param theta_ Angle of turn
       */
      Position(float x_, float y_, float theta_);
    };

    /**
     * Manages odometry data and position tracking of robot
     */
    class PositionManager {
    public:
      PositionManager();
    private:
      // Start position of robot
      unique_ptr<Position> startPos;
      // Last calculated position of robot
      unique_ptr<Position> lastPos;
      // Current calculated position of robot
      unique_ptr<Position> currentPos;

      /**
       * Updates current position calculation
       * @param lfEncoder Top Left Wheel Encoder value
       * @param lbEncoder Back Left Wheel Encoder value
       * @param rfEncoder Top Right Wheel Encoder value
       * @param rbEncoder Back Right Wheel Encoder value
       */
      void updateCalculation(int tlEncoder, int blEncoder, int trEncoder, int brEncoder);
    };
  }
#endif
