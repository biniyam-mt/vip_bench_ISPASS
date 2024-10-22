BENCHMARK_DIRS="boyer-moore-search bubble-sort distinctness edit-distance fft-int flood-fill gcd-list image-filters kadane kepler-calc knapsack lda minspan mnist-cnn nonlinear-nn nr-solver parrando primal-test set-intersect shortest-path"
# BENCHMARK_DIRS="minspan distinctness"

curDIR=$PWD

for dir in $BENCHMARK_DIRS; do

    # echo "Compiling $dir"
    # echo "Press any key to continue..."
    # while [ true ] ; do
    #     read -t 3 -n 1
    #     if [ $? = 0 ] ; then
    #     break ;
    #     fi
    # done

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

    #make clean
    #make 'MODE=enc'
    #mv $dir.enc bin/
    
    make clean
    cd $curDIR



done


