#include "structure/avl.h"

static inline int get_height(avl_node_t *node) {
  return (node == NULL) ? 0 : node->height;
}

static inline int get_balance(avl_node_t *node) {
  return (node == NULL) ? 0 : get_height(node->left) - get_height(node->right);
}

avl_node_t *rotate_right(avl_node_t *node) {
  avl_node_t *aux1 = node->left;
  avl_node_t *aux2 = aux1->right;

  aux1->right = node;
  node->left = aux2;

  node->height = max(get_height(node->left), get_height(node->right)) + 1;
  aux1->height = max(get_height(aux1->left), get_height(aux1->right)) + 1;
  
  return aux1;
}

avl_node_t *rotate_left(avl_node_t *node) {
  avl_node_t *aux1 = node->right;
  avl_node_t *aux2 = aux1->left;

  aux1->left = node;
  node->right = aux2;

  node->height = max(get_height(node->left), get_height(node->right)) + 1;
  aux1->height = max(get_height(aux1->left), get_height(aux1->right)) + 1;
  
  return aux1;
}

avl_node_t *avl_insert(avl_t *avl, avl_node_t *node, tuple_t key) {
  if (node == NULL) {
    avl_node_t *new = (avl_node_t *) malloc(sizeof(avl_node_t));

    new->key = key;
    new->left = NULL;
    new->right = NULL;
    new->height = 1;

    if (avl->root == NULL)
      avl->root = new;

    return new;
  }

  if (key.x < node->key.x)
    node->left  = avl_insert(avl, node->left, key);
  else
    node->right = avl_insert(avl, node->right, key);

  int balance = get_balance(node);
  node->height = max(get_height(node->left), get_height(node->right)) + 1;

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

void avl_to_array(avl_node_t *node, int *array, int *k) {
  if (node == NULL)
    return;

  avl_to_array(node->left, array, k);
  array[(*k)++] = node->key.y;
  avl_to_array(node->right, array, k);
}

avl_node_t *delete(avl_node_t *node) {
  if (node == NULL)
    return NULL;

  if (node->right != NULL)
    node->right = delete(node->right);
  else {
    avl_node_t *tmp = node->left;

    if (tmp == NULL) {
      tmp = node;
      node = NULL;
    } else
      *node = *tmp;

    free(tmp);
  }

  if (node == NULL)
    return NULL;

  int balance = get_balance(node);
  node->height = 1 + max(get_height(node->left), get_height(node->right));

  if (balance > 1 && get_balance(node->left) >= 0) {
    return rotate_right(node);
  } else if (balance > 1 && get_balance(node->left) < 0) {
    node->left = rotate_left(node->left);
    return rotate_right(node);
  } else if (balance < -1 && get_balance(node->right) <= 0) {
    return rotate_left(node);
  } else if (balance < -1 && get_balance(node->right) > 0) {
    node->right = rotate_right(node->right);
    return rotate_left(node);
  }

  return node;
}

void avl_remove_greatest(avl_t *avl) {
  avl->root = delete(avl->root);
}

tuple_t avl_get_smallest(avl_t *avl) {
  avl_node_t *node = avl->root;

  while (node->right != NULL)
    node = node->right;

  return node->key;
} 
