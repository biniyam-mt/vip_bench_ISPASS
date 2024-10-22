
LOCAL_CFLAGS= -I../common
LOCAL_LIBS=

PROG=do-modes/primal-test-${EXT}
OBJS=do-modes/primal-test-${EXT}.o ../common/utils.o

include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) $(TARGET_EXE) > FOO
	$(TARGET_DIFF) FOO primal-test.out
	rm -f FOO

