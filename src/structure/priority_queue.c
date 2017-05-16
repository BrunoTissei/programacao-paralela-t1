#include "structure/priority_queue.h"

void insert(priority_queue_t *pq, tuple_t key) {
  pq->tree.root = insert_avl(&(pq->tree), pq->tree.root, key);
  pq->size++;
}

tuple_t get_first(priority_queue_t *pq) {
  if (pq->size == 0) {
    return (tuple_t) {
      .x = 0,
      .y = 0
    };
  }

  return get_smallest(&(pq->tree));
}

void remove_last(priority_queue_t *pq) {
  remove_greatest(&(pq->tree));
  pq->size--;
}

void get_elements(priority_queue_t *pq, int *array) {
  int k = 0;
  get_y(pq->tree.root, array, &k);
}
