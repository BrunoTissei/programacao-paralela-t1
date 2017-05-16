#ifndef _PRIORITY_QUEUE_H
#define _PRIORITY_QUEUE_H

#include <stdio.h>

#include "structure/avl.h"

typedef struct priority_queue_t {
  int size;
  avl_t tree; 
} priority_queue_t;


void pq_insert(priority_queue_t *pq, tuple_t key);

tuple_t pq_first(priority_queue_t *pq);

void pq_remove_last(priority_queue_t *pq);

void pq_to_array(priority_queue_t *pq, int *array);

#endif
