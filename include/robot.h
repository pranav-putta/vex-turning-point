#ifndef ROBOT_H_
#define ROBOT_H_

#include <pathfinder.h>

#define WHEELBASE_WIDTH 0.17
#define WHEEL_RADIUS 0.04

#define MTR_BL 2
#define MTR_BR 3
#define MTR_TL 4
#define MTR_TR 5

#define MTR_LIFT_1 6
#define MTR_LIFT_2 7

#define MTR_FLY_1 8
#define MTR_FLY_2 9

#define MTR_CLAW 10

// Generate path of segments
Segment* generatePath(Waypoint* points);

// Generate main points, uses dijkstra's algorithm
Waypoint* generatePoints(Waypoint* currentPos, Waypoint* endPos);

// Use generated path to drive
// Pass a single waypoint
void driveToPoint(Waypoint* current, Waypoint* end);


#endif
