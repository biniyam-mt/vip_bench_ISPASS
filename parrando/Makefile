
LOCAL_CFLAGS=
LOCAL_LIBS=

PROG=do-modes/parrando-$(EXT)
OBJS=do-modes/parrando-$(EXT).o ../common/utils.o

include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) $(TARGET_EXE) > FOO
	$(TARGET_DIFF) FOO parrando.out
	rm -f FOO

