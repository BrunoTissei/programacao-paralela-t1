#ifndef _KNN_H
#define _KNN_H

#include "core/dataset.h"
#include "structure/balltree.h"

typedef struct knn_classifier_t {
  int k;
  balltree_t *balltree;
} knn_classifier_t;


knn_classifier_t *create_classifier(int k);

void fit(knn_classifier_t *knn_clf, set_t *tr_set);

int predict(knn_classifier_t *knn_clf, const point_t *point);

#endif
