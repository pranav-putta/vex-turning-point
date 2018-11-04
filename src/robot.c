#include "robot.h"

Segment* generatePath(Waypoint *points, int path_length) {
  TrajectoryCandidate candidate;

  // Create path segments
  // dt = 50ms, v = 1.0 m/s, a = 2.0 m/s, j = 10.0 m/s
  pathfinder_prepare(points, path_length, FIT_HERMITE_CUBIC, PATHFINDER_SAMPLES_HIGH,
  0.05, 1.0, 2.0, 10, &candidate);

  int length = candidate.length;

  Segment* trajectory = (Segment*) malloc(length * sizeof(Segment));

  // Generate and store path
  pathfinder_generate(&candidate, trajectory);

  return trajectory;
}

Waypoint* generatePoints(Waypoint *current, Waypoint *end) {

}

void driveToPoint(Waypoint *current, Waypoint *end) {
  Waypoint* points = generatePoints(current, end);
  free(current);
  free(end);

  int num_points = sizeof(points) / sizeof(Waypoint);
  Segment* trajectory = generatePath(points, num_points);

  Segment leftTrajectory[num_points];
  Segment rightTrajectory[num_points];

  // Create trajectory paths for left and right
  pathfinder_modify_tank(trajectory, num_points, leftTrajectory,
     rightTrajectory, WHEELBASE_WIDTH);

  free(trajectory);
  free(leftTrajectory);
  free(rightTrajectory);
  free(points);
}
