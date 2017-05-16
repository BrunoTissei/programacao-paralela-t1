#include "structure/avl.h"
#include <stdio.h>

int height(avl_node_t *node) {
  return (node == NULL) ? 0 : node->height;
}

avl_node_t *rotate_right(avl_node_t *y) {
  avl_node_t *x = y->left;
  avl_node_t *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  
  return x;
}

avl_node_t *rotate_left(avl_node_t *x) {
  avl_node_t *y = x->right;
  avl_node_t *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;
  
  return y;
}

avl_node_t *insert_avl(avl_t *avl, avl_node_t *node, tuple_t key) {
  if (node == NULL) {
    avl_node_t *n;

    //#pragma omp critical
    n = (avl_node_t *) malloc(sizeof(avl_node_t));

    n->key = key;
    n->left = NULL;
    n->right = NULL;
    n->height = 1;

    if (avl->root == NULL) {
      avl->root = n;
    }

    return n;
  }

  if (key.x < node->key.x) {
    node->left = insert_avl(avl, node->left, key);
  } else {
    node->right = insert_avl(avl, node->right, key);
  }

  int balance = 0;
  int left_h = height(node->left); 
  int right_h = height(node->right); 

  node->height = max(left_h, right_h) + 1;

  if (node != NULL) {
    balance = left_h - right_h; 
  }

  if (balance > 1 && key.x < node->left->key.x) {
    return rotate_right(node);
  } else if (balance < -1 && key.x > node->right->key.x) {
    return rotate_left(node);
  } else if (balance > 1 && key.x > node->left->key.x) {
    node->left = rotate_left(node->left);

    return rotate_right(node);
  } else if (balance < -1 && key.x < node->right->key.x) {
    node->right = rotate_right(node->right);

    return rotate_left(node);
  }

  return node;
}

void get_y(avl_node_t *node, int *array, int *k) {
  if (node == NULL) {
    return;
  }

  get_y(node->left, array, k);
  array[(*k)++] = node->key.y;
  get_y(node->right, array, k);
}

tuple_t remove_greatest(avl_t *avl) {
  avl_node_t *node = avl->root;
  avl_node_t *parent = NULL;

  while (node->right != NULL) {
    parent = node;
    node = node->right; 
  }

  tuple_t ret = node->key;

  if (parent == NULL) {
    //#pragma omp critical
    //free(avl->root);

    if (avl->root->left == NULL) {
      avl->root = NULL;
    } else {
      avl->root = avl->root->left;
    }
  } else {
    //#pragma omp critical
    //free(node);
    parent->right = NULL;
  }

  return ret;
}

tuple_t get_smallest(avl_t *avl) {
  avl_node_t *node = avl->root;

  while (node->left != NULL) {
    node = node->left;
  }

  return node->key;
} 
