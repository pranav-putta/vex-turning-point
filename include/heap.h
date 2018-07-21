#include "stdio.h"
#include <stdbool.h>

#ifndef MAX
#define MAX 100000
#endif

enum HeapMode {min, max};

struct HeapNode {
  int key, value;
};

struct Heap {
    int size;
    struct HeapNode *arr;
    enum HeapMode mode;
};

// FUNCTIONS

/* Constructor */
struct Heap create_heap(int size, struct HeapNode *arr, enum HeapMode *mode);
struct Heap create_empty_heap(enum HeapMode mode, int size);

/* Heap Reassembly */
void reconstruct_up(struct Heap *heap, int startIndex);
void reconstruct_down(struct Heap *heap);

bool compare(enum HeapMode *mode, int i, int j);

/* Node Retrieval Helper */
int get_parent_node_index(int childIndex);
int get_left_node_index(int parentIndex);
int get_right_node_index(int parentIndex);

/* Node Existance Helper */
bool has_parent(struct Heap *heap);
bool has_left(struct Heap *heap, int parentIndex);
bool has_right(struct Heap *heap, int parentIndex);

/* Helper methods */
void swap_nodes(struct Heap *heap, int i, int j);
void ensure_array_capacity(struct Heap *heap);

/* Accessor methods */
struct HeapNode peek(struct Heap *heap);
struct HeapNode poll(struct Heap *heap);

void update_node(struct Heap *heap, struct HeapNode *node);
bool contains_node(struct Heap *heap, int nodeKey);
bool is_empty(struct Heap *heap);
struct HeapNode find_node(struct Heap *heap, int nodeKey);
