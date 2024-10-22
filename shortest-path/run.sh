#!/bin/bash

gem5=${gem5:-clean} #clean, priv
version=${version:-native} #native, enc, enc-do
branch=${branch:-} #naive, shadow-reg, shadow-cache
bmk=${bmk:-} #name of bmk dir 
ext=${ext:-na} #na, no-cond, no-loop, no-mem

while [ $# -gt 0 ]; do
  case "$1" in
    --gem5=*)
      gem5="${1#*=}"
      ;;
    --version=*)
      version="${1#*=}"
      ;;
    --bmk=*)
      bmk="${1#*=}"
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


: ${GEM5_DIR:=~/privacy/gem5-versions/$gem5-gem5-$branch}
clean=clean
if [[ "$gem5" == "$clean" ]]; then
        GEM5_DIR=~/privacy/gem5-versions/$gem5-gem5
fi

BIN_DIR=bin
RESULT_DIR=results
CUR_DIR=$PWD

EXTRA_FLAG=' '
TEST=priv

if [[ "$gem5" == "$TEST" ]]; then
        EXTRA_FLAG='--debug-flags=Exec,priv,csd'
fi


CONFIG_FILE=$GEM5_DIR/configs/priv/do-modes-skylake/$bmk-$ext.py

cd $BIN_DIR

ln -sf $GEM5_DIR/ext/ ./ext

$GEM5_DIR/build/X86/gem5.opt $EXTRA_FLAG --debug-file=debug.out --stats-file=stats.txt $CONFIG_FILE

cd $CUR_DIR

mv $BIN_DIR/m5out $RESULT_DIR/m5out-$gem5-$ext-$(date +'%Y.%m.%d')
