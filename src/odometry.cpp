#include "robot.hpp"

using namespace robot;

long odometry::getEncoderVal(int motor) { return 1; }

location odometry::updateLocation(location current, Motor tl, Motor tr,
                                  Motor bl, Motor br) {
  long d_enc_tl = tl.getPosition() - last.tl;
  long d_enc_tr = tr.getPosition() - last.tr;
  long d_enc_bl = bl.getPosition() - last.bl;
  long d_enc_br = br.getPosition() - last.br;

  double aSL = (((d_enc_tl + d_enc_bl) / 2) / 900) * 2 * M_PI_4 * WHEEL_SIZE.getValue() * 0.5;
  double aSR = (((d_enc_tr + d_enc_br) / 2) / 900) * 2 * M_PI_4 * WHEEL_SIZE.getValue() * 0.5;
  double dS = (aSL + aSR) / 2;
  QAngle dTheta = QAngle((aSR - aSL) / BASE_SIZE.getValue());

  QLength dx = QLength(dS * std::cos((current.theta + dTheta / 2).getValue()));
  QLength dy = QLength(dS * std::sin((current.theta + dTheta / 2).getValue()));

  return location(current.x + dx, current.y + dy, current.theta + dTheta);
}
