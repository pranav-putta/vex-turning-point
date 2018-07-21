#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

// Empty Node
struct HeapNode empty_node = {.key = -1, .value = -1};

/* Initialize heap */
struct Heap create_heap(int size, struct HeapNode *arr, enum HeapMode *mode) {
  struct Heap heap;
  heap.size = size;
  heap.arr = arr;
  heap.mode = *mode;

  return heap;
}

/* Initialize heap with MAX nodes */
struct Heap create_empty_heap(enum HeapMode mode, int size) {
  struct Heap heap;

  // Setup nodes
  heap.arr = (HeapNode *) malloc(sizeof(HeapNode) * size);

  for (int i = 0; i < size; i++) {
    struct HeapNode filler = {.key = i, .value = MAX};
    heap.arr[i] = filler;
  }

  // Set size
  heap.size = size;
  // Set mode to min or max
  heap.mode = mode;

  return heap;
}

/* Re-heapify upwards */
void reconstruct_up(struct Heap *heap, int index) {
  // While a parent exists, and the parent is greater/lesser than child
  while(has_parent(heap) && !compare(&heap->mode,
     heap->arr[get_parent_node_index(index)].value,
     heap->arr[index].value)) {
      // Swap nodes
      swap_nodes(&heap->arr[get_parent_node_index(index)], &heap->arr[index]);
      index = get_parent_node_index(index);
    }
}

/* Re-heapify downards */
void reconstruct_down(struct Heap *heap) {
  int index = 0;

  // While left node exists
  while (has_left(heap, index)) {
    int smallChildIndex = get_left_node_index(index);
    // If right node exists and right node is smaller/bigger than left
    if (has_right(heap, index) && compare(&heap->mode,
      heap->arr[get_right_node_index(index)].value,
      heap->arr[get_left_node_index(index)].value)) {
      smallChildIndex = get_right_node_index(index);
    }

    if (!compare(&heap->mode, heap->arr[index].value, heap->arr[smallChildIndex].value)) {
      swap_nodes(&heap->arr[index], &heap->arr[smallChildIndex]);
    }
  }
}

/* Returns inndex of parent node */
int get_parent_node_index(int childIndex) {
  return (childIndex - 1) / 2;
}

/* Returns index of left child node */
int get_left_node_index(int parentIndex) {
  return (parentIndex * 2) + 1;
}

/* Returns index of right child node */
int get_right_node_index(int parentIndex) {
  return (parentIndex * 2) + 2;
}

/* Checks if parent node exists */
bool has_parent(struct Heap *heap) {
  bool hasParent = heap->size > 0;
  return hasParent;
}

/* Checks if left child node exists */
bool has_left(struct Heap *heap, int parentIndex) {
  bool hasLeft = get_left_node_index(parentIndex) < heap->size;
  return hasLeft;
}

/* Checks if right child node exists */
bool has_right(struct Heap *heap, int parentIndex) {
  bool hasRight = get_right_node_index(parentIndex) < heap->size;
  return hasRight;
}

// Swaps two heap nodes
void swap_nodes(struct HeapNode *i, struct HeapNode *j) {
  HeapNode temp = *i;
  // Switches values of pointers
  *i = *j;
  *j = temp;
}

/* Reallocates memory to ensure
that there is enough space */
void ensure_array_capacity(struct Heap *heap) {
  int arrSize = sizeof(heap->arr) / sizeof(heap->arr[0]);
  if (heap->size == arrSize) {
    heap->arr = (HeapNode *) realloc(heap->arr,
      sizeof(HeapNode) * (heap->size + 1));
  }
}

/* Delete min node and reheapify. Return min node */
struct HeapNode poll(struct Heap *heap) {
  if (heap->size != 0) {
    // Get node at top of heap
    struct HeapNode item = heap->arr[0];

    // Swap bottom and top nodes
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->arr[heap->size - 1] = empty_node;
    heap->size = heap->size - 1;

    // Heapify nodes
    reconstruct_down(heap);
    return item;
  }

  // Return empty if no items in heap
  return empty_node;
}

/* Return min node */
struct HeapNode peek(struct Heap *heap) {
  // Return first item in heap
  if (heap->size != 0) {
    return heap->arr[0];
  }

  // Return empty if no items in heap
  return empty_node;
}

/* Update node */
void update_node(struct Heap *heap, struct HeapNode *node) {
  int index = -1;

  // Find index
  for (int i = 0; i < heap->size; i++) {
    if (node->key == heap->arr[i].key) {
      index = i;
    }
  }

  // Swap node
  if (index != -1) {
    heap->arr[index] = *node;
    reconstruct_up(heap, index);
  }
}

/* Check if heap size is 0 */
bool is_empty(struct Heap *heap) {
  bool isEmpty = heap->size == 0;
  return isEmpty;
}

/* Check if heap contains node */
bool contains_node(struct Heap *heap, int nodeKey) {
  // Iterate through all nodes
  for (int i = 0; i < heap->size; i++) {
    // Check if node key is equal to input key
    if (heap->arr[i].key != -1 && heap->arr[i].key == nodeKey) {
      return true;
    }
  }

  return false;
}

/* Locate and return node given key */
struct HeapNode find_node(struct Heap *heap, int nodeKey) {
  for (int i = 0; i < heap->size; i++) {
    if (heap->arr[i].key == nodeKey) {
      return heap->arr[i];
    }
  }
  return empty_node;
}

/* Compare node values based on mode */
bool compare(enum HeapMode *mode, int i, int j) {
  if (*mode == min) {
    return i < j;
  } else {
    return j < i;
  }
}
