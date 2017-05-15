#include <stdio.h>
#include <stdlib.h>

#include "core/dataset.h"
#include "core/knn.h"
#include "util/io.h"

int main(int argc, char **argv) {
  int k = atoi(argv[3]);
  set_t *training_set = read_input_data(argv[1]);
  set_t *testing_set = read_input_data(argv[2]);

  knn_classifier_t *knn = create_knn_classifier(k);
  knn_fit(knn, training_set);

  int corr = 0;
  for (int i = 0; i < testing_set->size; ++i) {
    //int pred = predict(knn, testing_set.data[i]);
    int pred = 1;

    if (pred == testing_set->data[i]->mclass) {
      corr++;
    }
  }

  double accuracy = ((double) corr) / ((double) testing_set->size);
  printf("Accuracy: %lf\n", accuracy);
  return 0;
}
