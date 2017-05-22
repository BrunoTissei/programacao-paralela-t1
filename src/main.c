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
    return 1;
  }

  int correct = 0, iteration = 0;
  int k = atoi(argv[3]);
  set_t *training_set, *testing_set;

  if ((training_set = read_input_data(argv[1])) == NULL) {
    printf("ERRO: arquivo %s nao encontrado.\n", argv[1]);
    return 1;
  }

  if ((testing_set = read_input_data(argv[2])) == NULL) {
    printf("ERRO: arquivo %s nao encontrado.\n", argv[2]);
    return 1;
  }

  knn_classifier_t *knn = create_classifier(k);

	double start = timestamp();
  fit(knn, training_set);
  double building_time = timestamp() - start;

  start = timestamp();
  #pragma omp parallel for reduction (+:correct) shared(knn, testing_set)
  for (int i = 0; i < testing_set->size; ++i) {
    int pred = predict(knn, testing_set->data[i]);

    printf("%d/%d\r", iteration, testing_set->size);
    if (pred == testing_set->data[i]->mclass)
      correct++;

    #pragma omp atomic
    iteration++;
  }
  printf("%d/%d\n", testing_set->size, testing_set->size);

  double searching_time = timestamp() - start;

  delete_classifier(knn);


  double accuracy = ((double) correct) / ((double) testing_set->size);
  printf("Accuracy: %lf\n\n", accuracy);
  
	printf("Building time: %.0lf ms\n", building_time);
	printf("Searching time: %.0lf ms\n", searching_time);
  return 0;
}
