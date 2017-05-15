#include "structure/balltree.h"

balltree_t *create_tree(set_t *dataset, int k) {
  balltree_t *balltree = (balltree_t *) malloc(sizeof(balltree_t));

  balltree->dataset = dataset;
  balltree->k = k;
  balltree->root = build_tree(dataset, k);

  return balltree;
}

node_t *build_tree(set_t *points, int k) {
  node_t *node = (node_t *) malloc(sizeof(node_t));
  node->center = calc_center(points);
  
  if (points->size <= k) {
    node->points = points;
    /*node->points = create_set(points->size);
    for (int i = 0; i < points->size; ++i) {
      node->points->data[i] = points->data[i]; 
    }*/

    node->leaf = TRUE;
    node->left = NULL;
    node->right = NULL;
  } else {
    int left_idx = 0;
    set_t *left_part;
    set_t *right_part;

    node->radius = calc_radius(node->center, points, &left_idx);
    partition(points, &left_part, &right_part, left_idx);

    node->leaf = FALSE;
    node->left = build_tree(left_part, k);
    node->right = build_tree(right_part, k);
  }

  return node;
}

int *search(const point_t *point, int k) {

  return 0;
}

void recursive_search(node_t *node, const point_t *point, priority_queue *pq) {

}

void partition(set_t *points, set_t **left, set_t **right, int left_ind) {
  int right_ind = 0;
  double dist, grt_dist = 0.0;
  double left_dist, right_dist;

  point_t *rm_point;
  point_t *lm_point = points->data[left_ind];

  for (int i = 0; i < points->size; ++i) {
    dist = distance(lm_point, points->data[i]);

    if (dist > grt_dist) {
      grt_dist = dist;
      right_ind = i;
    }
  }

  rm_point = points->data[right_ind];
  int *left_idxs = (int *) malloc(sizeof(int) * points->size);
  int *right_idxs = (int *) malloc(sizeof(int) * points->size);
  int ri = 0, li = 0;

  for (int i = 0; i < points->size; ++i) {
    left_dist = distance(lm_point, points->data[i]);
    right_dist = distance(rm_point, points->data[i]);

    if (left_dist < right_dist) {
      left_idxs[li++] = i;
    } else {
      right_idxs[ri++] = i;
    }
  }

  *left = create_set(li);
  *right = create_set(ri);

  for (int i = 0; i < li; ++i) {
    left[0]->data[i] = points->data[left_idxs[i]];
  }

  for (int i = 0; i < ri; ++i) {
    right[0]->data[i] = points->data[right_idxs[i]];
  }

  free(left_idxs);
  free(right_idxs);
}

point_t *calc_center(set_t *points) {
  int n_dim = points->data[0]->size;
  point_t *center = create_point(n_dim);

  for (int i = 0; i < points->size; ++i) {
    for (int j = 0; j < n_dim; ++j) {
      center->value[j] += points->data[i]->value[j];
    }
  }
  
  double div = 1.0 / ((double) points->size);
  for (int i = 0; i < n_dim; ++i) {
    center->value[i] *= div;
  }

  return center;
}

double calc_radius(point_t *center, set_t *points, int *index) {
  double dist, radius = 0.0;

  for (int i = 0; i < points->size; ++i) {
    dist = distance(center, points->data[i]);

    if (radius < dist) {
      radius = dist;
      *index = i;
    }
  }

  return radius;
}
