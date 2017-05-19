#include "structure/heap.h"

heap_t *heap_create(int size) {
  heap_t *heap = (heap_t *) malloc(sizeof(heap_t));

  heap->size = size;
  heap->array = (tuple_t *) malloc(sizeof(tuple_t) * size);

  return heap;
}
