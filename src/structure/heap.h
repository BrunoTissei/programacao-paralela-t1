#ifndef _HEAP_H
#define _HEAP_H

#include <stdlib.h>
#include "util/types.h"

typedef struct heap_t {
  int size;
  tuple_t *array;
} heap_t;

heap_t *heap_create(int size);



#endif
