bench=$1
RED='\033[0;31m'
GREEN='\033[0;92m'
GREY='\033[0;33m'
NC='\033[0m' # No Color
./scripts/build-clean.sh $bench
cd ./$bench/bin

rm *.out
./$bench-na.do | tail -n +2 > 1.out
./$bench-no-loop.do | tail -n +2 > 2.out
./$bench-no-cond.do | tail -n +2 >  3.out
./$bench-no-mem.do | tail -n +2 >  4.out
clear

DIFF1=$(diff 1.out 2.out)
DIFF2=$(diff 1.out 3.out)
DIFF3=$(diff 1.out 4.out)
echo Testing $bench
if [ -f $bench-no-loop.do ]; then
    if [ "$DIFF1" != "" ] 
    then
        echo "na - loop: ${RED}FAIL${NC}"
    else
        echo "na - loop: ${GREEN}PASS${NC}"
    fi
else
    echo "na - loop: ${GREY}N/A${NC}"

fi

if [ -f $bench-no-cond.do ]; then
    if [ "$DIFF2" != "" ] 
    then
        echo "na - cond: ${RED}FAIL${NC}"
    else
        echo "na - cond: ${GREEN}PASS${NC}"
    fi
else
    echo "na - cond: ${GREY}N/A${NC}"
fi

if [ -f $bench-no-mem.do ]; then
    if [ "$DIFF3" != "" ] 
    then
        echo "na - mem:  ${RED}FAIL${NC}"
    else
        echo "na - mem:  ${GREEN}PASS${NC}"
    fi
else
        echo "na - mem:  ${GREY}N/A${NC}"
fi
rm *.out