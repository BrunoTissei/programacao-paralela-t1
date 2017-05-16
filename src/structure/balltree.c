#include "structure/balltree.h"

balltree_t *create_tree(set_t *dataset, int k) {
  balltree_t *balltree = (balltree_t *) malloc(sizeof(balltree_t));

  balltree->dataset = dataset;
  balltree->k = k;


  #pragma omp parallel
  {
    #pragma omp single
    balltree->root = build_tree(dataset, k);
  }

  return balltree;
}

node_t *build_tree(set_t *points, int k) {
  node_t *node;

  //#pragma omp critical
  node = (node_t *) malloc(sizeof(node_t));
  node->center = calc_center(points);
  
  if (points->size <= k) {
    node->points = points;

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

    #pragma omp task
    node->left = build_tree(left_part, k);
    #pragma omp task
    node->right = build_tree(right_part, k);

    #pragma omp taskwait
  }

  return node;
}

int *search(balltree_t *bt, const point_t *point, int k) {
  priority_queue_t pq;
  pq.size = 0;
  pq.tree.root = NULL;
  recursive_search(bt, bt->root, point, &pq);
  int *result;
  
  //#pragma omp critical
  result = (int *) malloc(sizeof(int) * pq.size);

  get_elements(&pq, result);
  for (int i = 0; i < pq.size; ++i) {
    result[i] = bt->dataset->data[result[i]]->mclass;
  }

  return result;
}

void recursive_search(balltree_t *bt, node_t *node, const point_t *point, priority_queue_t *pq) {
  tuple_t top = get_first(pq);

  if (node->leaf) {
    for (int i = 0; i < node->points->size; ++i) {
      double dist = distance(point, node->points->data[i]);
    
      if (pq->size == 0 || dist < distance(point, bt->dataset->data[top.y])) {
        tuple_t entry = {
          .x = dist,
          .y = node->points->data[i]->id
        };

        insert(pq, entry);
        if (pq->size > bt->k) {
          remove_last(pq); 
        }
      }
    }
  } else {
    double dist_left = distance(point, node->left->center);
    double dist_right = distance(point, node->right->center);

    if (dist_left <= dist_right) {
      if (!pq->size || dist_left <= top.x + node->left->radius) {
        recursive_search(bt, node->left, point, pq);
      }

      if (!pq->size || (dist_right <= top.x + node->right->radius)) {
        recursive_search(bt, node->right, point, pq);
      }
    } else {
      if (!pq->size || (dist_right <= top.x + node->right->radius)) {
        recursive_search(bt, node->right, point, pq);
      }

      if (!pq->size || dist_left <= top.x + node->left->radius) {
        recursive_search(bt, node->left, point, pq);
      }
    }
  }
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

  int ri = 0, li = 0;
  int *left_idxs, *right_idxs;

  //#pragma omp critical
  left_idxs = (int *) malloc(sizeof(int) * points->size);
  //#pragma omp critical
  right_idxs = (int *) malloc(sizeof(int) * points->size);

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

  //#pragma omp critical
  free(left_idxs);
  //#pragma omp critical
  free(right_idxs);
}

point_t *calc_center(set_t *points) {
  int n_dim = points->data[0]->size;
  point_t *center;

  center = create_point(n_dim, -1);

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
