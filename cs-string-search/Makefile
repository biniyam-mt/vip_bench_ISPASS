
LOCAL_CFLAGS=
LOCAL_LIBS=

PROG=cs-modes/string-search-$(EXT)
OBJS=cs-modes/string-search-$(EXT).o ../common/utils.o

include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) $(TARGET_EXE) > FOO
	-$(TARGET_DIFF) FOO string-search.out
	rm -f FOO

