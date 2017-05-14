#ifndef _KNN_H
#define _KNN_H

#include "core/dataset.h"
#include "structure/balltree.h"

typedef struct knn_classifier_t {
  int k;
  balltree_t *balltree;
} knn_classifier_t;


knn_classifier_t *create_knn_classifier(int k);

void knn_fit(knn_classifier_t *knn_clf, set_t *tr_set);

#endif
