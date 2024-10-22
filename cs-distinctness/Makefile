
LOCAL_CFLAGS=-I../common
LOCAL_LIBS=

PROG=cs-modes/distinctness-$(EXT)
OBJS=cs-modes/distinctness-$(EXT).o ../common/utils.o

include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) $(TARGET_EXE) > FOO
	-$(TARGET_DIFF) FOO distinctness.out
	rm -f FOO

