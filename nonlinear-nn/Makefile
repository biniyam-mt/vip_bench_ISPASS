
LOCAL_CFLAGS=
LOCAL_LIBS=

PROG=do-modes/nonlinear-nn-$(EXT)
OBJS=do-modes/nonlinear-nn-$(EXT).o ../common/utils.o

include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) $(TARGET_EXE) > FOO
	$(TARGET_DIFF) FOO nonlinear-nn.out
	rm -f FOO

