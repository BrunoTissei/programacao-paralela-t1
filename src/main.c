#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "core/dataset.h"
#include "core/knn.h"
#include "util/io.h"
#include "structure/priority_queue.h"

int main(int argc, char **argv) {
  int k = atoi(argv[3]);
  set_t *training_set = read_input_data(argv[1]);
  set_t *testing_set = read_input_data(argv[2]);

  knn_classifier_t *knn = create_knn_classifier(k);
  knn_fit(knn, training_set);

  int corr = 0;

  #pragma omp parallel for reduction (+:corr) shared(knn, testing_set)
  for (int i = 0; i < testing_set->size; ++i) {
    int pred = predict(knn, testing_set->data[i]);

    //printf("%d\n", i);
    if (pred == testing_set->data[i]->mclass) {
      corr++;
    }
  }

  double accuracy = ((double) corr) / ((double) testing_set->size);
  printf("Accuracy: %lf\n", accuracy);
 /* 
  priority_queue_t pq;
  pq.size = 0;
  pq.tree.root = NULL;

  for (int i = 10; i >= 0; --i) {
    tuple_t entry = {
      .x = (double) i,
      .y = i
    };

    insert(&pq, entry);
  }

  int *res = (int *) malloc(sizeof(int) * 100);
  get_elements(&pq, res);
  for (int i = 0; i < 10; ++i) {
    printf("%d\n", res[i]);
  }
*/
  return 0;
}
