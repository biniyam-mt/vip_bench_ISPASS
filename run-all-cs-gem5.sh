#!/bin/bash

gem5=${gem5:-clean} #clean, priv
version=${version:-native} #native, enc, enc-do
branch=${branch:-} #naive, shadow-reg, shadow-cache
ext=${ext:-na} #na, no-cond, no-loop, no-mem
inp=${inp:-128} #na, no-cond, no-loop, no-mem

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
    --inp=*)
      inp="${1#*=}"
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
BENCHMARK_DIRS_NA="distinctness sort string-search"
BENCHMARK_DIRS_OG="distinctness sort string-search"
BENCHMARK_DIRS_F1="distinctness sort string-search"
BENCHMARK_DIRS_F2="distinctness sort string-search"

BENCHMARK_DIRS=""
if [[ "$ext" == "na" ]]; then
	BENCHMARK_DIRS=$BENCHMARK_DIRS_NA
elif [[ "$ext" == "og" ]]; then
	BENCHMARK_DIRS=$BENCHMARK_DIRS_OG
elif [[ "$ext" == "f1" ]]; then
	BENCHMARK_DIRS=$BENCHMARK_DIRS_F1
elif [[ "$ext" == "f2" ]]; then
	BENCHMARK_DIRS=$BENCHMARK_DIRS_F2
else
  printf "ERROR Invalid EXT Given\n"
  exit 1
fi

# BENCMARK_DIRS="bubble-sort" #MANUAL OVERRIDE

curDIR=$PWD

for dir in $BENCHMARK_DIRS; do
    # mv $dir/results $dir/O0-results
    # mkdir $dir/results
    cd cs-$dir
    ./run.sh --bmk=$dir --gem5='clean' --version='do' --ext=$ext --inp=$inp | tee results/run-$inp-$ext-$(date +'%Y.%m.%d').out &
    cd $curDIR
done
