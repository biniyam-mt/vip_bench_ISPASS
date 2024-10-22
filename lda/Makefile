
LOCAL_CFLAGS=
LOCAL_LIBS=

PROG=do-modes/lda-$(EXT)
OBJS=do-modes/lda-$(EXT).o ../common/utils.o ../common/mathlib.o

include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) $(TARGET_EXE) > FOO
	$(TARGET_DIFF) FOO lda.out
	rm -f FOO

