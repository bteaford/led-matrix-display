CXXFLAGS=-Wall -O3 -g -Wextra -Wno-unused-parameter

BIN_DIR := bin
OBJ_DIR := $(BIN_DIR)/obj

RGB_LIB_DISTRIBUTION=lib/rpi-rgb-led-matrix
RGB_INCDIR=$(RGB_LIB_DISTRIBUTION)/include
RGB_LIBDIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread

all: $(BIN_DIR)/ChristmasCountdown

$(BIN_DIR)/ChristmasCountdown: $(OBJ_DIR)/ChristmasCountdown.o

$(RGB_LIBRARY): FORCE
	$(MAKE) -C $(RGB_LIBDIR)

$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(RGB_LIBRARY)
	@mkdir -p $(BIN_DIR)
	$(CXX) $< -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.cc
	@mkdir -p $(OBJ_DIR)
	$(CXX) -I$(RGB_INCDIR) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BIN_DIR)

FORCE:
.PHONY: FORCE