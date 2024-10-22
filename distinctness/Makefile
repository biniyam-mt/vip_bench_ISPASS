
LOCAL_CFLAGS= -I../common
LOCAL_LIBS=

PROG=distinctness
PROG=do-modes/distinctness-$(EXT)
OBJS=do-modes/distinctness-$(EXT).o ../common/utils.o

include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) ./$(TARGET_EXE) > FOO 
	$(TARGET_DIFF) FOO distinctness.out
	rm -f FOO

