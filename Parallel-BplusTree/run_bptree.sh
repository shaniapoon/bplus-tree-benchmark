#!/bin/bash

WORKLOAD=$1
OPS=50000

for t in 1 2 4 8 16 32
do
  for i in 1 2 3
  do
    OUTPUT=$(./bpbench $t $OPS | grep Throughput | awk '{print $2}')
    echo "$WORKLOAD,bptree,$t,$OUTPUT" >> bptree_results.csv
    sleep 1
  done
done
