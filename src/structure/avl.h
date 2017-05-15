#ifndef _AVL_H
#define _AVL_H

#include "util/types.h"

typedef struct avl_node_t {
  tuple_t element;
  struct avl_node_t *left;
  struct avl_node_t *right;
} avl_node_t;

typedef struct avl_t {
  avl_node_t *root;
} avl_t;


void insert(avl_t *avl, tuple_t number);

tuple_t remove_greatest(avl_t *avl);

tuple_t get_smallest(avl_t *avl);

#endif
