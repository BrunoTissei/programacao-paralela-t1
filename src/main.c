#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "core/dataset.h"
#include "core/knn.h"
#include "util/io.h"
#include "structure/priority_queue.h"

int main(int argc, char **argv) {
  if (argc < 4) {
    print_usage();
  }

  int correct = 0, iteration = 0;
  int k = atoi(argv[3]);

  set_t *training_set = read_input_data(argv[1]);
  set_t *testing_set = read_input_data(argv[2]);

  knn_classifier_t *knn = create_classifier(k);
  fit(knn, training_set);


  #pragma omp parallel for reduction (+:correct) shared(knn, testing_set)
  for (int i = 0; i < testing_set->size; ++i) {
    int pred = predict(knn, testing_set->data[i]);

    printf("%d/%d\r", iteration, testing_set->size);
    if (pred == testing_set->data[i]->mclass) {
      correct++;
    }

    #pragma omp atomic
    iteration++;
  }

  delete_classifier(knn);

  printf("%d/%d\n", testing_set->size, testing_set->size);


  double accuracy = ((double) correct) / ((double) testing_set->size);
  printf("Accuracy: %lf\n", accuracy);
  
  return 0;
}
