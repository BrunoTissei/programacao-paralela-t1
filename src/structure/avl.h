#ifndef _AVL_H
#define _AVL_H

#include <stdlib.h>

#include "util/types.h"

typedef struct avl_node_t {
  tuple_t key;
  int height;
  struct avl_node_t *left;
  struct avl_node_t *right;
} avl_node_t;

typedef struct avl_t {
  avl_node_t *root;
} avl_t;


avl_node_t *insert_avl(avl_t *avl, avl_node_t *node, tuple_t key);

void remove_greatest(avl_t *avl);

void get_y(avl_node_t *node, int *array, int *k);

tuple_t get_smallest(avl_t *avl);

#endif
