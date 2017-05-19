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

int search(balltree_t *bt, const point_t *point, int *result);

void delete_nodes(node_t *n);

void delete_balltree(balltree_t *balltree);

node_t *build_tree(set_t *points, int k);

void recursive_search(balltree_t *bt, node_t *node, const point_t *point, 
    priority_queue_t *pq);

void partition(set_t *points, set_t **left, set_t **right, int left_ind);

void calc_center(set_t *points, point_t **center);

double calc_radius(point_t *center, set_t *points, int *index);

#endif
