
LOCAL_CFLAGS= -I../common
LOCAL_LIBS=

PROG=do-modes/gcd-list-$(EXT)
OBJS=do-modes/gcd-list-$(EXT).o ../common/utils.o

include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) ./$(TARGET_EXE) > FOO 
	$(TARGET_DIFF) FOO gcd-list.out
	rm -f FOO

