#!/bin/bash

gem5=${gem5:-clean} #clean, priv
version=${version:-native} #native, enc, enc-do
branch=${branch:-} #naive, shadow-reg, shadow-cache
ext=${ext:-na} #na, no-cond, no-loop, no-mem


while [ $# -gt 0 ]; do
  case "$1" in
    --gem5=*)
      gem5="${1#*=}"
      ;;
    --version=*)
      version="${1#*=}"
      ;;
    --branch=*)
      branch="${1#*=}"
      ;;
    --ext=*)
      ext="${1#*=}"
      ;;
    *)
      printf "***************************\n"
      printf "* Error: Invalid argument.*\n"
      printf "***************************\n"
      exit 1
  esac
  shift
done

#!/bin/bash
BENCHMARK_HOME_DIR=./
BENCHMARK_DIRS_NA="distinctness flood-fill primal-test boyer-moore-search bubble-sort edit-distance fft-int gcd-list image-filters kadane kepler-calc knapsack lda minspan mnist-cnn nonlinear-nn nr-solver parrando set-intersect shortest-path"
BENCHMARK_DIRS_LOOP="distinctness flood-fill primal-test boyer-moore-search bubble-sort fft-int gcd-list kepler-calc nr-solver parrando"
BENCHMARK_DIRS_COND="distinctness flood-fill primal-test boyer-moore-search bubble-sort edit-distance fft-int gcd-list image-filters kadane kepler-calc knapsack lda minspan mnist-cnn nonlinear-nn nr-solver parrando set-intersect shortest-path"
BENCHMARK_DIRS_MEM="distinctness boyer-moore-search knapsack minspan parrando"

BENCHMARK_DIRS=""
if [[ "$ext" == "na" ]]; then
	BENCHMARK_DIRS=$BENCHMARK_DIRS_NA
elif [[ "$ext" == "no-loop" ]]; then
	BENCHMARK_DIRS=$BENCHMARK_DIRS_LOOP
elif [[ "$ext" == "no-cond" ]]; then
	BENCHMARK_DIRS=$BENCHMARK_DIRS_COND
elif [[ "$ext" == "no-mem" ]]; then
	BENCHMARK_DIRS=$BENCHMARK_DIRS_MEM
else
  printf "ERROR Invalid EXT Given\n"
  exit 1
fi

# BENCMARK_DIRS="bubble-sort" #MANUAL OVERRIDE

curDIR=$PWD

for dir in $BENCHMARK_DIRS; do
    # mv $dir/results $dir/O0-results
    # mkdir $dir/results
    cp run.sh $dir/
    cd $dir
    ./run.sh --bmk=$dir --gem5='clean' --version='do' --ext=$ext | tee results/run-$ext-$(date +'%Y.%m.%d').out &
    cd $curDIR
done
