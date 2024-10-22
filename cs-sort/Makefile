
LOCAL_CFLAGS=-I../common
LOCAL_LIBS=

PROG=cs-modes/sort-$(EXT)
OBJS=cs-modes/sort-$(EXT).o ../common/utils.o

include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) $(TARGET_EXE) > FOO
	-$(TARGET_DIFF) FOO sort.out
	rm -f FOO

