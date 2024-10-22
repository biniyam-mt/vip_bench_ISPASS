
LOCAL_CFLAGS= -I../common
LOCAL_LIBS=

PROG=do-modes/shortest-path-$(EXT)
OBJS=do-modes/shortest-path-$(EXT).o ../common/utils.o


include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) $(TARGET_EXE) > FOO
	$(TARGET_DIFF) FOO shortest-path.out
	rm -f FOO

