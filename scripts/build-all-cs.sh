BENCHMARK_DIRS="distinctness flood-fill sort string-search"

curDIR=$PWD

for dir in $BENCHMARK_DIRS; do

    cd cs-$dir
    rm -r bin
    mkdir bin
    
    make clean
    make 'MODE=do' 'EXT=na'
    mv cs-modes/$dir-na.do bin/
    
    make clean
    make 'MODE=do' 'EXT=og'
    mv cs-modes/$dir-og.do bin/

    make clean
    make 'MODE=do' 'EXT=f1'
    mv cs-modes/$dir-f1.do bin/

    make clean
    make 'MODE=do' 'EXT=f2'
    mv cs-modes/$dir-f2.do bin/
    
    make clean
    cd $curDIR

done


