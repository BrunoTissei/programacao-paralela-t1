#ifndef _BALL_TREE_H
#define _BALL_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "core/dataset.h"
#include "util/types.h"
#include "structure/priority_queue.h"

typedef struct node_t {
  set_t *points;
  point_t *center;

  BOOL leaf;
  double radius;
  struct node_t *left, *right;
} node_t;

typedef struct balltree_t {
  int k;
  node_t *root;
  set_t *dataset;
} balltree_t;


balltree_t *create_balltree(set_t *dataset, int k);

void search(balltree_t *bt, const point_t *point, int *result);

#endif
