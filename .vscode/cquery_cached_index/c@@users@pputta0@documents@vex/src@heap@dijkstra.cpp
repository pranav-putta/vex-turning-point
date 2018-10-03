#include "dijkstra.h"
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

// Calculates shortest distance path
int* dijkstra_shortest_path(struct GraphNode *nodes, int startNodeKey, int endNodeKey) {
  int size = sizeof(*nodes) / sizeof(nodes[0]);
  int *shortestDistances = (int *) malloc(sizeof(int) * size);
  int counter = 0;

  // Initialize minHeap of size
  struct Heap minHeap = create_empty_heap(min, size);
  struct HeapNode toUpdate = {.key = startNodeKey, .value = 0};
  update_node(&minHeap, &toUpdate);

  // Run until heap is empty
  while (!is_empty(&minHeap)) {
    // Poll top node in heap
    struct HeapNode u = poll(&minHeap);

    // Iterate through adjecent edges
    int size = sizeof(*nodes[u.key].edgeKeys) / sizeof(nodes[u.key].edgeKeys[0]);
    for (int i = 0; i < size; i++) {
      // If heap contains key, update value if distance is shorter
      if (contains_node(&minHeap, nodes[u.key].edgeKeys[i])) {
        // Calculate distance
        int distance = u.value + nodes[u.key].edgeDistances[i];
        int currentValue = find_node(&minHeap, nodes[u.key].edgeKeys[i]).value;

        // If the distance value is less than current, update
        if (distance < currentValue) {
          struct HeapNode newNode = {.key = nodes[u.key].edgeKeys[i], .value = distance};
          update_node(&minHeap, &newNode);
        }
      }
    }

      // Add to short distance list
      shortestDistances[counter] = u.value;
      counter++;
  }

  return shortestDistances;
}
