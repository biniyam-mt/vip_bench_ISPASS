include ../config.mk

#
# END of user-modifiable variables
#

ifeq ($(MODE), na)
TARGET_CFLAGS = $(NA_CFLAGS)
TARGET_LIBS = $(NA_LIBS)
TARGET_SIM = $(NA_SIM)
TARGET_DIFF = $(NA_DIFF)
TARGET_EXE = $(PROG).na
else ifeq ($(MODE), do)
TARGET_CFLAGS = $(DO_CFLAGS)
TARGET_LIBS = $(DO_LIBS)
TARGET_SIM = $(DO_SIM)
TARGET_DIFF = $(DO_DIFF)
ifeq ($(PROG), image-filters)
ifdef EXT
	TARGET_EXE = do-modes/$(PROG)-$(EXT).do
endif
else
TARGET_EXE = $(PROG).do
endif
else ifeq ($(MODE), enc)
TARGET_CFLAGS = $(ENC_CFLAGS)
TARGET_LIBS = $(ENC_LIBS)
TARGET_SIM = $(ENC_SIM)
TARGET_DIFF = $(ENC_DIFF)
TARGET_EXE = $(PROG).enc
else
# default is native
TARGET_CFLAGS = $(NA_CFLAGS)
TARGET_LIBS = $(NA_LIBS)
TARGET_SIM = $(NA_SIM)
TARGET_DIFF = $(NA_DIFF)
TARGET_EXE = $(PROG).na
endif

CFLAGS = -std=c++11 -Wall $(OPT_CFLAGS) -Wno-strict-aliasing $(TARGET_CFLAGS) $(LOCAL_CFLAGS) -rdynamic
LIBS = $(LOCAL_LIBS) $(TARGET_LIBS)

build: $(TARGET_EXE)

%.o: %.cpp
ifeq ($(MODE), na)
	$(CXX) $(CFLAGS) -DVIP_NA_MODE -o $(notdir $@) -c $<
else ifeq ($(MODE), do)
	$(CXX) $(CFLAGS) -DVIP_DO_MODE -o $(notdir $@) -c $<
else ifeq ($(MODE), enc)
	$(CXX) $(CFLAGS) -DVIP_ENC_MODE -o $(notdir $@) -c $<
else
	$(error MODE is not defined (add: MODE={na|do|enc}).)
endif

%.o: %.c
ifeq ($(MODE), na)
	$(CC) $(CFLAGS) -DVIP_NA_MODE -o $(notdir $@) -c $<
else ifeq ($(MODE), do)
	$(CC) $(CFLAGS) -DVIP_DO_MODE -o $(notdir $@) -c $<
else ifeq ($(MODE), enc)
	$(CC) $(CFLAGS) -DVIP_ENC_MODE -o $(notdir $@) -c $<
else
	$(error MODE is not defined (add: MODE={na|do|enc}).)
endif

$(TARGET_EXE): $(OBJS)
	$(LD) $(CFLAGS) -o $@ $(notdir $^) $(LIBS)

clean:
	rm -f *.o *.do *.enc *.na core do-modes/*.out do-modes/*.do do-modes/*.enc do-modes/*.na do-modes/*.o FOO $(LOCAL_CLEAN)
	rm -f *.o *.do *.enc *.na core cs-modes/*.out cs-modes/*.do cs-modes/*.enc cs-modes/*.na cs-modes/*.o FOO $(LOCAL_CLEAN)		