#ifndef ROBOT_H_
#define ROBOT_H_

#include "main.h"

struct Flag {
private:
  float verticalDistLow;
  float verticalDistHigh;
  Flag(float low, float high): verticalDistLow(low), verticalDistHigh(high){}
public:
  const Flag HIGH;
  const Flag LOW;

};
#endif
