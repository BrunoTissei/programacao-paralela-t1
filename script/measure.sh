#!/bin/bash

echo "$1 $2"

for i in $(seq 1 $1)
do
  export OMP_NUM_THREADS=$i

  for j in $(seq 1 $2)
  do
    times=`./knn data/training_set data/testing_set 1 | awk -F ' ' '{ print $3 }' | tail -n 2 | sed 's| ms||g'`
    echo $times
  done
done
