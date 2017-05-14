#include "core/dataset.h"

point_t *create_point(unsigned int size) {
  point_t *p = (point_t *) malloc(sizeof(point_t));

  p->size = size;
  p->value = (double *) malloc(size * sizeof(double));

  return p;
}

set_t *create_set(unsigned int size) {
  set_t *s = (set_t *) malloc(sizeof(set_t));

  s->size = size;
  s->data = (point_t **) malloc(size * sizeof(point_t *));

  return s;
}

double distance(point_t *a, point_t *b) {
  if (a->size != b->size)
    printf("%d %d\n", a->size, b->size);
  assert(a->size == b->size);

  double dist = 0.0;

  for (int i = 0; i < a->size; ++i) {
    dist += (a->value[i] - b->value[i]) * (a->value[i] - b->value[i]);
  }

  return (dist);
}
