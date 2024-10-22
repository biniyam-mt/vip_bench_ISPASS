BENCHMARK_DIRS="boyer-moore-search bubble-sort distinctness edit-distance fft-int flood-fill gcd-list image-filters kadane kepler-calc knapsack lda minspan mnist-cnn nonlinear-nn nr-solver parrando primal-test set-intersect shortest-path"
# BENCHMARK_DIRS="minspan distinctness"

curDIR=$PWD

# for dir in $BENCHMARK_DIRS; do
#     echo "Press any key to continue..."
#     while [ true ] ; do
#         read -t 3 -n 1
#         if [ $? = 0 ] ; then
#         break ;
#         fi
#     done
#     ./scripts/check.sh $dir


# done


for dir in $BENCHMARK_DIRS; do
    cd $dir/bin
    
    echo "Press any key to continue..."
    while [ true ] ; do
        read -t 3 -n 1
        if [ $? = 0 ] ; then
        break ;
        fi
    done

    if [ "$dir" = "kepler-calc" ]; then
        DIFF="numdiff -r 0.001"
    else
        DIFF="diff"
    fi

    echo "$dir----------------------------"

    ./$dir-na.do > na.out 2> $curDIR/TEMP
    if [[ -f "$dir-no-loop.do" ]]; then
        echo -e '\t' " no-loop--------------"
        ./$dir-no-loop.do > no-loop.out 2> $curDIR/TEMP
        $DIFF na.out no-loop.out | sed 's/^/        /'
    fi

    if [[ -f "$dir-no-cond.do" ]]; then
        echo -e '\t' " no-cond--------------"
        ./$dir-no-cond.do > no-cond.out 2> $curDIR/TEMP
        $DIFF na.out no-cond.out | sed 's/^/        /'
    fi

    if [[ -f "$dir-no-mem.do" ]]; then
        echo -e '\t' " no-mem--------------"
        ./$dir-no-mem.do > no-mem.out 2> $curDIR/TEMP
        $DIFF na.out no-mem.out | sed 's/^/        /'
    fi

    cd $curDIR
done


