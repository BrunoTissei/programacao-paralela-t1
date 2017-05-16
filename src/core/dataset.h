#ifndef _DATA_SET_H
#define _DATA_SET_H

#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <immintrin.h>

typedef struct point_t {
  int size;
  int mclass, id;
  double *value;
} point_t;

typedef struct set_t {
  int size;
  point_t **data;
} set_t;


point_t *create_point(unsigned int size, int id);

set_t *create_set(unsigned int size);

double distance(const point_t *a, const point_t *b);

#endif
