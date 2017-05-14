#ifndef _BALL_TREE_H
#define _BALL_TREE_H

#include "core/dataset.h"
#include "util/types.h"
#include "structure/priority_queue.h"
#include <stdio.h>

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


balltree_t *create_tree(set_t *dataset, int k);

node_t *build_tree(set_t *points, int k);

int *search(const point_t *point, int k);

void recursive_search(node_t *node, const point_t *point, priority_queue *pq);

void partition(set_t *points, set_t **left, set_t **right, int left_ind);

point_t *calc_center(set_t *points);

double calc_radius(point_t *center, set_t *points, int *index);

#endif
