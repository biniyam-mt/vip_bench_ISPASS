
LOCAL_CFLAGS= -I../common
LOCAL_LIBS=

PROG=do-modes/fft-int-$(EXT)
OBJS=do-modes/fft-int-$(EXT).o ../common/mathlib.o ../common/utils.o

include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) $(TARGET_EXE) > FOO
	$(TARGET_DIFF) FOO fft-int.out
	rm -f FOO

