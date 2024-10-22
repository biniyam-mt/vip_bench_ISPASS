
LOCAL_CFLAGS= -I../common
LOCAL_LIBS=
LOCAL_CLEAN=FOO.bmp

PROG=do-modes/image-filters-$(EXT)
OBJS=do-modes/image-filters-$(EXT).o do-modes/helpers-$(EXT).o ../common/utils.o ../common/mathlib.o

include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) ./$(TARGET_EXE) -s original.bmp FOO.bmp
	$(TARGET_DIFF) FOO.bmp image-filters.out
	rm -f FOO.bmp
	-$(TARGET_SIM) ./$(TARGET_EXE) -e original.bmp FOO.bmp
	$(TARGET_DIFF) FOO.bmp image-filters1.out
	rm -f FOO.bmp
