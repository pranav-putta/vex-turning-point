#ifndef UTIL_H_
#define UTIL_H_

#include "main.h"
#include <math.h>
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
     * Manages odometry data and position tracking of robot
     */
    class PositionManager {
    public:
      PositionManager();

      /**
       * Updates current position calculation
       * @param lfEncoder Top Left Wheel Encoder value
       * @param lbEncoder Back Left Wheel Encoder value
       * @param rfEncoder Top Right Wheel Encoder value
       * @param rbEncoder Back Right Wheel Encoder value
       */
      void updateCalculation(int tlEncoder, int blEncoder, int trEncoder, int brEncoder);

      /**
       * Retrieve current position of robot
       * @return [Point holding current position]
       */
      okapi::Point& getCurrentPosition();
    private:
      // Start position of robot
      unique_ptr<okapi::Point> startPos;
      // Last calculated position of robot
      unique_ptr<okapi::Point> lastPos;
      // Current calculated position of robot
      unique_ptr<okapi::Point> currentPos;
    };

    /**
     * PathManager holds the map of the field as a matrix
     * Allows
     */
    class PathManager {
    public:
      /**
       * Function that returns the only instance of Path Manager.
       * Creates a new instance if does not exist already
       * @return [description]
       */
      static PathManager& instance();

      /**
       * Uses Dijkstra's algorithm to find the shortest path between two points
       * @param  initial [Initial position]
       * @param  target [Target position]
       * @return    [a generated path of points]
       */
      initializer_list<okapi::Point> calculateShortestPath(okapi::Point &initial, okapi::Point &target);

      /**
       * Calculates launch speed needed using kinematics
       * @param  current [current position]
       * @param  target [target flag]
       * @return         [V0 initial velocity of ball]
       */
      okapi::QSpeed calculateLaunchSpeed(okapi::Point &current, Flag &target);

      /**
       * Calculates launch base angle needed using trigonometry
       * @param  current [current position]
       * @param  target [target flag]
       * @return         [angle needed from base]
       */
      okapi::QAngle calculateLaunchBaseAngle(okapi::Point &current, Flag &target);

    private:
      // Default constructor private
      PathManager();
      // instance
      static unique_ptr<PathManager> m_pInstance;

    };
  }
#endif
