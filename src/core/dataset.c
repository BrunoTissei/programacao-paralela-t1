#include "core/dataset.h"

point_t *create_point(unsigned int size, int id) {
  point_t *p = (point_t *) malloc(sizeof(point_t));

  p->id = id;
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

double distance(const point_t *a, const point_t *b) {
  int i = 0, n = a->size - (a->size % 4);
  double dist = 0.0;

  __m256d ma, mb, msub, mans;

  for (i = 0; i < n; i += 4) {
    ma = _mm256_loadu_pd(&(a->value[i]));
    mb = _mm256_loadu_pd(&(b->value[i]));

    msub = _mm256_sub_pd(ma, mb);
    msub = _mm256_mul_pd(msub, msub);

    mans = _mm256_hadd_pd(msub, msub);
    dist += ((double *) &mans)[0] + ((double *) &mans)[2];
  }

  for ( ; i < a->size; ++i)
    dist += (a->value[i] - b->value[i]) * (a->value[i] - b->value[i]);

  return dist;
}
