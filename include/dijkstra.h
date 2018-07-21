#include "stdio.h"

/**
* Struct that represents a node on path graph
*
* key -- tail node
* edgeKeys -- edge heads associated with tail node
* edgeDistances -- distances for each corresponding edge
*/
struct GraphNode {
  int key;
  int *edgeKeys;
  int *edgeDistances;
};

int* dijkstra_shortest_path(struct GraphNode *nodes, int startNodeKey, int endNodeKey);
