
LOCAL_CFLAGS= -Wno-unused-function -Wno-unused-result -Wno-strict-aliasing -I../common
LOCAL_LIBS=

PROG=do-modes/mnist-cnn-$(EXT)
OBJS=do-modes/mnist-cnn-$(EXT).o do-modes/kautodiff-$(EXT).o do-modes/kann-$(EXT).o do-modes/kann_data-common.o ../common/mathlib.o ../common/utils.o

include ../Makefile

test: $(TARGET_EXE)
	-$(TARGET_SIM) $(TARGET_EXE) -i mnist-cnn.kan mnist-test-x.knd > FOO
	$(TARGET_DIFF) FOO mnist-cnn-infer.out
	rm -f FOO
	-$(TARGET_SIM) $(TARGET_EXE) -o mnist-data.kan mnist-train-x.knd mnist-train-y.knd > FOO
	$(TARGET_DIFF) FOO mnist-cnn-train.out
	rm -f FOO

