
LOCAL_CFLAGS= -I../common
LOCAL_LIBS=

PROG=do-modes/kadane-$(EXT)
OBJS=do-modes/kadane-$(EXT).o ../common/utils.o

include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) $(TARGET_EXE) > FOO
	$(TARGET_DIFF) FOO kadane.out
	rm -f FOO

