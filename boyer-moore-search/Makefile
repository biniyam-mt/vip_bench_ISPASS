
LOCAL_CFLAGS=
LOCAL_LIBS=

PROG=do-modes/boyer-moore-search-$(EXT)
OBJS=do-modes/boyer-moore-search-$(EXT).o ../common/utils.o

include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) $(TARGET_EXE) > FOO
	-$(TARGET_DIFF) FOO boyer-moore-search.out
	rm -f FOO

