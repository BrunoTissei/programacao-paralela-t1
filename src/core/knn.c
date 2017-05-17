#include "core/knn.h"

knn_classifier_t *create_classifier(int k) {
  knn_classifier_t *knn = (knn_classifier_t *) malloc(sizeof(knn_classifier_t));
  knn->k = k;

  return knn;
}

void fit(knn_classifier_t *knn_clf, set_t *tr_set) {
  knn_clf->balltree = create_balltree(tr_set, knn_clf->k);
}

int predict(knn_classifier_t *knn_clf, const point_t *point) {
  int ans;
  int *result = (int *) malloc(sizeof(int) * knn_clf->k);

  search(knn_clf->balltree, point, result);

  ans = result[0];
  free(result);

  return ans; 
}
