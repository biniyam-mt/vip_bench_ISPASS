

LOCAL_CFLAGS= -I../common
LOCAL_LIBS=

PROG=do-modes/kepler-calc-$(EXT)
OBJS=do-modes/kepler-calc-$(EXT).o ../common/mathlib.o ../common/utils.o

include ../Makefile

DO_DIFF= numdiff -r 0.001
ENC_DIFF=$(DO_DIFF)

test:
	-$(TARGET_SIM) $(TARGET_EXE) > FOO
	$(TARGET_DIFF) FOO kepler-calc.out
	rm -f FOO

