
LOCAL_CFLAGS= -I../common
LOCAL_LIBS=

PROG=do-modes/set-intersect-$(EXT)
OBJS=do-modes/set-intersect-$(EXT).o ../common/utils.o

include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) ./$(TARGET_EXE) > FOO 
	$(TARGET_DIFF) FOO set-intersect.out
	rm -f FOO

