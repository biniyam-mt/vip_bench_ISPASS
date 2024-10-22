
LOCAL_CFLAGS=-I../common
LOCAL_LIBS=

PROG=cs-modes/flood-fill-$(EXT)
OBJS=cs-modes/flood-fill-$(EXT).o ../common/utils.o

include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) $(TARGET_EXE) > FOO
	-$(TARGET_DIFF) FOO flood-fill.out
	rm -f FOO

