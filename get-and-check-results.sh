curDIR=$PWD
EXT=$1
DATE=$2
CONT=$3

BENCHMARK_DIRS_NA=" boyer-moore-search bubble-sort distinctness edit-distance fft-int flood-fill gcd-list image-filters kadane kepler-calc knapsack lda minspan mnist-cnn nonlinear-nn nr-solver parrando primal-test set-intersect shortest-path"
BENCHMARK_DIRS_LOOP="boyer-moore-search bubble-sort distinctness fft-int flood-fill gcd-list kepler-calc nr-solver parrando primal-test "
BENCHMARK_DIRS_COND=" boyer-moore-search bubble-sort distinctness edit-distance fft-int flood-fill gcd-list image-filters kadane kepler-calc knapsack lda minspan mnist-cnn nonlinear-nn nr-solver parrando primal-test set-intersect shortest-path"
BENCHMARK_DIRS_MEM="boyer-moore-search distinctness knapsack minspan parrando"
# BENCHMARK_DIRS_NA="flood-fill edit-distance"
# BENCHMARK_DIRS_LOOP="flood-fill"
# BENCHMARK_DIRS_COND="flood-fill edit-distance"
# BENCHMARK_DIRS_MEM="minspan"

BENCHMARK_DIRS=""
if [[ "$EXT" == "na" ]]; then
	BENCHMARK_DIRS=$BENCHMARK_DIRS_NA
elif [[ "$EXT" == "no-loop" ]]; then
	BENCHMARK_DIRS=$BENCHMARK_DIRS_LOOP
elif [[ "$EXT" == "no-cond" ]]; then
	BENCHMARK_DIRS=$BENCHMARK_DIRS_COND
elif [[ "$EXT" == "no-mem" ]]; then
	BENCHMARK_DIRS=$BENCHMARK_DIRS_MEM
else
  printf "ERROR Invalid EXT Given\n"
  exit 1
fi

RED='\033[0;31m'
GREEN='\033[0;32m'
GREY='\033[0;33m'
NC='\033[0m' # No Color

#print aggregate results via python
python3 get-stats.py print $EXT $DATE > stats.txt


echo "------------------------------------------"
for dir in $BENCHMARK_DIRS; do
    
    if [[ "$CONT" == "y" ]]; then
        while [ true ] ; do
            read -t 3 -n 1
            if [ $? = 0 ] ; then
            break ;
            fi
        done
    fi

    python3 get-stats.py $dir $EXT $DATE  >> stats.txt

    cd $dir/bin
    
    if [ "$dir" = "kepler-calc" ]; then
        DIFF="numdiff -r 0.001"
    else
        DIFF="diff" 
    fi

    printf "${GREEN}$dir${NC} \n"
    echo "------------------------------------------"
    printf "   ${GREEN}$dir${NC} output diff:\n"

    ./$dir-na.do > FOO.out 2> FOO.err
    $DIFF FOO.out ../results/m5out-clean-$EXT-$DATE/$dir-$EXT.do.out | grep -v "[VIP]" | sed 's/^/        /' #Ignore lines for rdtsc cycle count...
    rm FOO.out
    rm FOO.err

    printf "   ${GREEN}$dir${NC} error grep:\n"
    grep "ERROR" ../results/m5out-clean-$EXT-$DATE/debug.out | sed 's/^/        /'

    printf "   ${GREEN}$dir${NC} cycle count:\n"
    IFS=':' read -ra vip <<<  $(grep "VIP" ../results/m5out-clean-$EXT-$DATE/$dir-$EXT.do.out)
    IFS=' ' read -ra vip2 <<<  ${vip[1]}
    echo -n ${vip2[0]} "-- " | sed 's/^/        /'
    grep "VIP" ../results/m5out-clean-$EXT-$DATE/$dir-$EXT.do.out

    IFS=' ' read -ra stat <<<  $( grep "system.cpu.numCycles" ../results/m5out-clean-$EXT-$DATE/stats.txt | sed -n '2 p')
    echo -n ${stat[1]} "-- " | sed 's/^/        /'
    grep "system.cpu.numCycles" ../results/m5out-clean-$EXT-$DATE/stats.txt | sed -n '2 p' 

    if test ${vip2[0]} != ${stat[1]}; then  
        printf "        ${RED}cycle counts differ${NC}\n"
    fi

    echo "------------------------------------------"
    cd $curDIR
done

cat stats.txt