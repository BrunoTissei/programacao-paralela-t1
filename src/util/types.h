#ifndef _TYPES_H
#define _TYPES_H

#define TRUE 1
#define FALSE 0

typedef unsigned short BOOL;

typedef struct tuple_t {
  double x;
  int y;
} tuple_t;

#define max(a, b) ((a > b) ? a : b)
#define min(a, b) ((a < b) ? a : b)

#endif
