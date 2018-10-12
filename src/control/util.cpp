#include "util.h"

using namespace std;
using namespace okapi;

namespace robot::util {

  /// Position Manager class definition ///

  PositionManager::PositionManager() {
    // Initialize all members to default
    startPos = make_unique<okapi::Point>();
    lastPos = make_unique<okapi::Point>();
    currentPos = make_unique<okapi::Point>();
  }

  // TODO:
  // 900 ticks per revolution
  void PositionManager::updateCalculation(int tlEncoder, int blEncoder,
                                              int trEncoder, int lrEncoder) {
      double encoderFactor = ((4 * M_PI) / 900);
      double displacement = (tlEncoder + blEncoder + trEncoder + lrEncoder) * encoderFactor;
      QAngle theta (((trEncoder + lrEncoder) - (tlEncoder +blEncoder)) * (encoderFactor / 12));

      QLength dx (displacement * cos((currentPos->theta + theta / 2).getValue()));
      QLength dy (displacement * sin((currentPos->theta + theta / 2).getValue()));

      lastPos->x = currentPos->x;
      lastPos->y = currentPos->y;
      lastPos->theta = currentPos->theta;

      dx += lastPos->x;
      dy += lastPos ->y;
      theta += lastPos->theta;

      currentPos->x = dx;
      currentPos->y = dy;
      currentPos->theta = theta;
      }

  okapi::Point& PositionManager::getCurrentPosition() {
    return *currentPos.get();
  }

  /// Path Manager class definition ///
  unique_ptr<PathManager> PathManager::m_pInstance = NULL;

  PathManager& PathManager::instance() {
    // Check if instance is running
    if (!m_pInstance) {
      m_pInstance = make_unique<PathManager>(PathManager());
    }

    return *m_pInstance.get();
  }

  //TODO: Implement
  initializer_list<okapi::Point> PathManager::calculateShortestPath(okapi::Point &initial, okapi::Point &target) {
  }

  //TODO: Implement
  okapi::QSpeed PathManager::calculateLaunchSpeed(okapi::Point &initial, Flag &target) {

  }

  //TODO: implement
  okapi::QAngle PathManager::calculateLaunchBaseAngle(okapi::Point &initial, Flag &target) {

  }
}
