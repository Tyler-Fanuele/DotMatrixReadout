CFLAGS=-Wall -O3 -g -Wextra -Wno-unused-parameter
CXXFLAGS=$(CFLAGS)

# Allow optional Image/GraphicsMagick++ flags when available. The shell
# calls are no-ops on systems without the tools (they'll return empty).
MAGICK_CXXFLAGS?=$(shell GraphicsMagick++-config --cppflags --cxxflags 2>/dev/null || Magick++-config --cxxflags 2>/dev/null || echo)
MAGICK_LDFLAGS?=$(shell GraphicsMagick++-config --ldflags --libs 2>/dev/null || Magick++-config --libs 2>/dev/null || echo)

SRCDIR=src
OBJDIR=build
OBJECTS=$(OBJDIR)/display.o \
	$(OBJDIR)/matrixWidget.o $(OBJDIR)/matrixDrawable.o
BINARIES=$(OBJDIR)/display

RGB_LIB_DISTRIBUTION=./lib/rpi-rgb-led-matrix/
RGB_INCDIR=$(RGB_LIB_DISTRIBUTION)/include
RGB_LIBDIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread

all : $(BINARIES)

$(RGB_LIBRARY): FORCE
	$(MAKE) -C $(RGB_LIBDIR)

$(OBJDIR)/display.o : $(SRCDIR)/main.cxx
	$(CXX) $(CXXFLAGS) $(MAGICK_CXXFLAGS) -c $< -o $@

$(OBJDIR)/matrixWidget.o : $(SRCDIR)/matrixWidget.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/matrixDrawable.o : $(SRCDIR)/matrixDrawable.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/display : $(OBJDIR)/display.o $(OBJDIR)/matrixDrawable.o $(OBJDIR)/matrixWidget.o
	$(CXX) $^ -o $@ $(LDFLAGS) $(MAGICK_LDFLAGS)

clean:
	rm -f $(OBJECTS) $(BINARIES)

FORCE:
.PHONY: FORCE