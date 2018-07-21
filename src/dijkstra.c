#include "dijkstra.h"
#include "heap.h"

// TODO: FIX BUGS

int* dijkstra_shortest_path(struct GraphNode *nodes, int startNodeKey, int endNodeKey) {
  int shortestDistances[1000];
  int size = sizeof(nodes) - 1;
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


      shortestDistances[counter] = u.value;
      counter++;
  }

  int* x = shortestDistances;
  return x;
}

/*int main() {
  struct GraphNode arr[3];
  int e0[1] = {2};
  int ed0[1] = {2};
  int e1[1] = {2};
  int ed1[1] ={3};

  int e2[0];
  int ed2[0];

  arr[0].key = 0;
  arr[0].edgeKeys = e0;
  arr[0].edgeDistances = ed0;
  arr[1].key = 1;
  arr[1].edgeKeys = e1;
  arr[1].edgeDistances = ed1;
  arr[2].key = 2;
  arr[2].edgeKeys = e2;
  arr[2].edgeDistances = ed2;


  int *x = dijkstra_shortest_path(arr, 0, 2);*/

}
