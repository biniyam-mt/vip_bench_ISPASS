
LOCAL_CFLAGS=
LOCAL_LIBS=

PROG=do-modes/edit-distance-$(EXT)
OBJS=do-modes/edit-distance-$(EXT).o ../common/utils.o

include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) $(TARGET_EXE) > FOO
	$(TARGET_DIFF) FOO edit-distance.out
	rm -f FOO

