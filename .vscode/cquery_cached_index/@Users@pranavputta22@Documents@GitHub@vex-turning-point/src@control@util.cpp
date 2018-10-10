#include "util.h"

using namespace std;

namespace robot::util {

  /// Position Manager class definition ///

  PositionManager::PositionManager() {
    // Initialize all members to default
    startPos = make_unique<okapi::Point>();
    lastPos = make_unique<okapi::Point>();
    currentPos = make_unique<okapi::Point>();
  }

  // TODO: implement
  void PositionManager::updateCalculation(int tlEncoder, int blEncoder,
                                              int trEncoder, int lrEncoder) {

  }

  okapi::Point& PositionManager::getCurrentPosition() {
    return *currentPos.get();
  }

  /// Path Manager class definition ///
  unique_ptr<PathManager> PathManager::m_pInstance = NULL;

  PathManager& PathManager::instance() {
    // Check if instance is running
    if (!m_pInstance) {
      m_pInstance = make_unique<PathManager>();
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
