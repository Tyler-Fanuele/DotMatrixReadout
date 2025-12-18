#include <led-matrix.h>
#include <graphics.h>
#include <Magick++.h>

#include <matrixTextWidget.h>
#include <matrixDateTimeClockWidget.h>
#include <matrixApp.h>

#include <getopt.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream>

#include <vector>
#include <string>

using namespace rgb_matrix;

const char* FontDirectoryString = "./lib/rpi-rgb-led-matrix/fonts/";
const char* LargeFontFileString = "7x14.bdf";
const char* SmallFontFileString = "4x6.bdf";

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
  interrupt_received = true;
}

static int usage(const char *progname) {
  fprintf(stderr, "usage: %s [options]\n", progname);
  fprintf(stderr, "Reads text from stdin and displays it. "
          "Empty string: clear screen\n");
  fprintf(stderr, "Options:\n");
  fprintf(stderr,
          "\t-d <time-format>  : Default '%%H:%%M'. See strftime()\n"
          "\t                    Can be provided multiple times for multiple "
          "lines\n"
          "\t-f <small-font-file>    : Use given font.\n"
          "\t-F <large-font-file>    : Use given font.\n"
          "\t-x <x-origin>     : X-Origin of displaying text (Default: 0)\n"
          "\t-y <y-origin>     : Y-Origin of displaying text (Default: 0)\n"
          "\t-s <line-spacing> : Extra spacing between lines when multiple -d given\n"
          "\t-S <spacing>      : Extra spacing between letters (Default: 0)\n"
          "\t-C <r,g,b>        : Color. Default 255,255,0\n"
          "\t-B <r,g,b>        : Background-Color. Default 0,0,0\n"
          "\t-O <r,g,b>        : Outline-Color, e.g. to increase contrast.\n"
          "\n"
          );
  rgb_matrix::PrintMatrixFlags(stderr);
  return 1;
}

static bool parseColor(Color *c, const char *str) {
  return sscanf(str, "%hhu,%hhu,%hhu", &c->r, &c->g, &c->b) == 3;
}

static bool FullSaturation(const Color &c) {
  return (c.r == 0 || c.r == 255)
    && (c.g == 0 || c.g == 255)
    && (c.b == 0 || c.b == 255);
}

int main(int argc, char *argv[]) {
  // Initialize ImageMagick / GraphicsMagick++ library before any Magick++ use.
  Magick::InitializeMagick(*argv);

  MatrixApp* app = new MatrixApp(argc, argv);

  MatrixDateTimeClockWidget* dateTimeClock = new MatrixDateTimeClockWidget(nullptr);

  app->setRootWidget(dateTimeClock);

  app->run();

  delete app;

  std::cout << std::endl;  // Create a fresh new line after ^C on screen
  return 0;
}
