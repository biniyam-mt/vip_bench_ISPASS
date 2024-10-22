
LOCAL_CFLAGS= -I../common
LOCAL_LIBS=

PROG=do-modes/minspan-$(EXT)
OBJS=do-modes/minspan-$(EXT).o ../common/utils.o

include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) ./$(TARGET_EXE) > FOO 
	$(TARGET_DIFF) FOO minspan.out
	rm -f FOO

