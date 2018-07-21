#include "heap.h"

struct Heap create_heap(int size, struct HeapNode *arr, enum HeapMode *mode) {
  struct Heap heap = {.size = size, .arr = arr, .mode = *mode};
  heap.size = size;
  heap.arr = arr;
  heap.mode = *mode;

  return heap;
}

struct Heap create_empty_heap(enum HeapMode mode, int size) {
  struct Heap heap;
  struct HeapNode nodes[1000];

  for (int i = 0; i < size; i++) {
    struct HeapNode filler = {.key = i, .value = MAX};
    nodes[i] = filler;
  }

  heap.size = size;
  heap.arr = nodes;
  heap.mode = mode;

  return heap;
}

void reconstruct_up(struct Heap *heap, int index) {
  // While a parent exists, and the parent is greater/lesser than child
  while(has_parent(heap) && !compare(&heap->mode,
     heap->arr[get_parent_node_index(index)].value,
     heap->arr[index].value)) {
      // Swap nodes
      swap_nodes(heap, get_parent_node_index(index), index);
      index = get_parent_node_index(index);
    }
}

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
      swap_nodes(heap, index, smallChildIndex);
    }
  }
}

int get_parent_node_index(int childIndex) {
  return (childIndex - 1) / 2;
}

int get_left_node_index(int parentIndex) {
  return (parentIndex * 2) + 1;
}

int get_right_node_index(int parentIndex) {
  return (parentIndex * 2) + 2;
}

bool has_parent(struct Heap *heap) {
  bool hasParent = heap->size > 0;
  return hasParent;
}

bool has_left(struct Heap *heap, int parentIndex) {
  bool hasLeft = get_left_node_index(parentIndex) < heap->size;
  return hasLeft;
}

bool has_right(struct Heap *heap, int parentIndex) {
  bool hasRight = get_right_node_index(parentIndex) < heap->size;
  return hasRight;
}

void swap_nodes(struct Heap *heap, int i, int j) {
  struct HeapNode temp = heap->arr[i];
  heap->arr[i] = heap->arr[j];
  heap->arr[j] = temp;
}

void ensure_array_capacity(struct Heap *heap) {
  int arrSize = sizeof(heap->arr) / sizeof(heap->arr[0]);
  if (heap->size == arrSize) {
    // TODO: Increase array size
  }
}

struct HeapNode poll(struct Heap *heap) {
  if (heap->size != 0) {
    struct HeapNode item = heap->arr[0];
    struct HeapNode empty = {.key = -1, .value = -1};
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->arr[heap->size - 1] = empty;
    heap->size--;
    reconstruct_down(heap);
    return item;
  }

  struct HeapNode empty = {.key = -1, .value = -1};
  return empty;
}

struct HeapNode peek(struct Heap *heap) {
  if (heap->size != 0) {
    return heap->arr[0];
  }

  struct HeapNode empty = {.key = -1, .value = -1};
  return empty;
}

void update_node(struct Heap *heap, struct HeapNode *node) {
  int index = -1;

  for (int i = 0; i < heap->size; i++) {
    if (node->key == heap->arr[i].key) {
      index = i;
    }
  }

  if (index != -1) {
    heap->arr[index] = *node;
    reconstruct_up(heap, index);
  }
}

bool is_empty(struct Heap *heap) {
  bool isEmpty = heap->size == 0;
  return isEmpty;
}

bool contains_node(struct Heap *heap, int nodeKey) {
  for (int i = 0; i < heap->size; i++) {
    if (heap->arr[i].key != -1 && heap->arr[i].key == nodeKey) {
      return true;
    }
  }

  return false;
}

struct HeapNode find_node(struct Heap *heap, int nodeKey) {
  for (int i = 0; i < heap->size; i++) {
    if (heap->arr[i].key == nodeKey) {
      return heap->arr[i];
    }
  }

  struct HeapNode empty = {.key = -1, .value = -1};
  return empty;
}

bool compare(enum HeapMode *mode, int i, int j) {
  if (*mode == min) {
    return i < j;
  } else {
    return j < i;
  }
}
