#ifndef _DATA_SET_H
#define _DATA_SET_H

#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

typedef struct point_t {
  int mclass;
  unsigned int size;
  double *value;
} point_t;

typedef struct set_t {
  unsigned int size;
  point_t **data;
} set_t;


set_t *create_set(unsigned int size);

point_t *create_point(unsigned int size);

double distance(point_t *a, point_t *b);

#endif
