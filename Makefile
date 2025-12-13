CFLAGS=-Wall -O3 -g -Wextra -Wno-unused-parameter
CXXFLAGS=$(CFLAGS)

SRCDIR=src/
OBJDIR=.
OBJECTS=$(OBJDIR)/display.o
BINARIES=display

RGB_LIB_DISTRIBUTION=./matrixLib/rpi-rgb-led-matrix/
RGB_INCDIR=$(RGB_LIB_DISTRIBUTION)/include
RGB_LIBDIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread

all : $(BINARIES)

$(RGB_LIBRARY): FORCE
	$(MAKE) -C $(RGB_LIBDIR)

display.o : src/main.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

display : display.o
	$(CXX) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJECTS) $(BINARIES)

FORCE:
.PHONY: FORCE