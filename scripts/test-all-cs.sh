BENCHMARK_DIRS="distinctness flood-fill sort string-search"

curDIR=$PWD

for dir in $BENCHMARK_DIRS; do

    echo "Press any key to continue..."
    while [ true ] ; do
        read -t 3 -n 1
        if [ $? = 0 ] ; then
        break ;
        fi
    done

    cd cs-$dir/bin
    
    if [ "$dir" = "kepler-calc" ]; then
        DIFF="numdiff -r 0.001"
    else
        DIFF="diff"
    fi

    echo "$dir----------------------------"

    ./$dir-na.do > na.out 2> $curDIR/TEMP
    if [[ -f "$dir-og.do" ]]; then
        echo -e '\t' " og--------------"
        ./$dir-og.do > og.out 2> $curDIR/TEMP
        $DIFF na.out og.out | sed 's/^/        /'
    fi

    if [[ -f "$dir-f1.do" ]]; then
        echo -e '\t' " f1--------------"
        ./$dir-f1.do > f1.out 2> $curDIR/TEMP
        $DIFF na.out f1.out | sed 's/^/        /'
    fi

    if [[ -f "$dir-f2.do" ]]; then
        echo -e '\t' " f2--------------"
        ./$dir-f2.do > f2.out 2> $curDIR/TEMP
        $DIFF na.out f2.out | sed 's/^/        /'
    fi


    cp $dir-na.do ../bbin/$dir-$1-na.do
    cp $dir-og.do ../bbin/$dir-$1-og.do
    cp $dir-f1.do ../bbin/$dir-$1-f1.do
    cp $dir-f2.do ../bbin/$dir-$1-f2.do

    cd $curDIR
done


