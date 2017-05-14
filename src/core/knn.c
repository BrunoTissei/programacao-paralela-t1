#include "core/knn.h"

knn_classifier_t *create_knn_classifier(int k) {
  knn_classifier_t *knn = (knn_classifier_t *) malloc(sizeof(knn_classifier_t));
  knn->k = k;

  return knn;
}

void knn_fit(knn_classifier_t *knn_clf, set_t *tr_set) {
  knn_clf->balltree = create_tree(tr_set, knn_clf->k);
  printf("Success!\n");
}
