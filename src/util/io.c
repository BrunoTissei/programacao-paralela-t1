#include "util/io.h"

set_t *read_input_data(char *filename) {
  int n, d;
  set_t *set;
  FILE *f = fopen(filename, "r");

  fscanf(f, "%d %d", &n, &d);

  set = create_set(n);
  for (int i = 0; i < n; ++i) {
    set->data[i] = create_point(d);

    for (int j = 0; j < d; ++j) {
      fscanf(f, "%lf", &(set->data[i]->value[j]));
    }

    fscanf(f, "%d", &(set->data[i]->mclass));
  }

  return set;
}
