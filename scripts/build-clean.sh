
dir=$1
#test-linear-reg bubble-sort edit-distance eulers-number-approx fft-int kepler-calc mersenne nonlinear-nn nr-solver parrando rad-to-degree lda triangle-count mnist-cnn"
# BENCHMARK_DIRS="boyer-moore-search mnist-cnn scalar-gwas-chi2 vector-gwas-chi2"

curDIR=$PWD

cd $dir
rm -r bin
mkdir bin

#make clean
#make 'MODE=na'
#mv $dir.na bin/

make clean
make 'MODE=do' 'EXT=na'
mv do-modes/$dir-na.do bin/

make clean
make 'MODE=do' 'EXT=no-loop'
mv do-modes/$dir-no-loop.do bin/

make clean
make 'MODE=do' 'EXT=no-cond'
mv do-modes/$dir-no-cond.do bin/

make clean
make 'MODE=do' 'EXT=no-mem'
mv do-modes/$dir-no-mem.do bin/


make clean
cd $curDIR



