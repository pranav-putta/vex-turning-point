#include "util.h"

using namespace std;

namespace robot::util {

  // Position struct definition
  Position::Position() {
    x = 0;
    y = 0;
    theta = 0;
  }

  Position::Position(float x_, float y_, float theta_) {
    x = x_;
    y = y_;
    theta = theta_;
  }

  // Position Manager class definition

  PositionManager::PositionManager() {
    // Initialize all members to default
    startPos = make_unique<Position>(Position());
    lastPos = make_unique<Position>(Position());
    currentPos = make_unique<Position>(Position());
  }

  // TODO: implement
  void PositionManager::updateCalculation(int tlEncoder, int blEncoder,
                                              int trEncoder, int lrEncoder) {

  }
}
