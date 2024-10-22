curDIR=$PWD
EXT=$1
DATE=$2
CONT=$3

BENCHMARK_DIRS="flood-fill"
INPS="10 15 20 25 32 45"
#"32 64 128 256 512 1024 2048"


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

        
    for inp in $INPS; do
    
        python3 get-stats.py cs-$dir $inp-$EXT $DATE  >> stats.txt

        cd cs-$dir/bin
        

        printf "${GREEN}$dir${NC} \n"
        echo "------------------------------------------"
        # printf "   ${GREEN}$dir${NC} output diff:\n"

        # ./$dir-na.do > FOO.out 2> FOO.err
        # diff FOO.out ../results/m5out-clean-$inp-$EXT-$DATE/$dir-$EXT.do.out | grep -v "[VIP]" | sed 's/^/        /' #Ignore lines for rdtsc cycle count...
        # rm FOO.out
        # rm FOO.err

        printf "   ${GREEN}$dir${NC} error grep:\n"
        grep "ERROR" ../results/m5out-clean-$inp-$EXT-$DATE/debug.out | sed 's/^/        /'

        printf "   ${GREEN}$dir${NC} cycle count:\n"
        IFS=':' read -ra vip <<<  $(grep "VIP" ../results/m5out-clean-$inp-$EXT-$DATE/$dir-$EXT.do.out)
        IFS=' ' read -ra vip2 <<<  ${vip[1]}
        echo -n ${vip2[0]} "-- " | sed 's/^/        /'
        grep "VIP" ../results/m5out-clean-$inp-$EXT-$DATE/$dir-$EXT.do.out

        IFS=' ' read -ra stat <<<  $( grep "system.cpu.numCycles" ../results/m5out-clean-$inp-$EXT-$DATE/stats.txt | sed -n '2 p')
        echo -n ${stat[1]} "-- " | sed 's/^/        /'
        grep "system.cpu.numCycles" ../results/m5out-clean-$inp-$EXT-$DATE/stats.txt | sed -n '2 p' 

        if test ${vip2[0]} != ${stat[1]}; then  
            printf "        ${RED}cycle counts differ${NC}\n"
        fi

        echo "------------------------------------------"
        cd $curDIR
    done
done

cat stats.txt