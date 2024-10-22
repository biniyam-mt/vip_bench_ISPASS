
LOCAL_CFLAGS= -I../common
LOCAL_LIBS=

PROG=do-modes/nr-solver-$(EXT)
OBJS=do-modes/nr-solver-$(EXT).o ../common/mathlib.o ../common/utils.o 

include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) $(TARGET_EXE) > FOO
	$(TARGET_DIFF) FOO nr-solver.out
	rm -f FOO

