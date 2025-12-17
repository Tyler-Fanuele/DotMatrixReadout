#include "../lib/rpi-rgb-led-matrix/include/led-matrix.h"
#include "../lib/rpi-rgb-led-matrix/include/graphics.h"
#include <Magick++.h>

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
  RGBMatrix::Options matrix_options;
  rgb_matrix::RuntimeOptions runtime_opt;
  if (!rgb_matrix::ParseOptionsFromFlags(&argc, &argv,
                                         &matrix_options, &runtime_opt)) {
    return usage(argv[0]);
  }

  // We accept multiple format lines

  std::vector<std::string> format_lines;
  Color color(255, 255, 0);
  Color bg_color(0, 0, 0);
  Color outline_color(0,0,0);
  bool with_outline = false;

  const char *bdf_large_font_file = NULL;
  const char *bdf_small_font_file = NULL;
  int x_orig = 0;
  int y_orig = 0;
  int letter_spacing = 0;
  int line_spacing = 0;

  int opt;
  while ((opt = getopt(argc, argv, "x:y:f:F:C:B:O:s:S:d:")) != -1) {
    switch (opt) {
    case 'd': format_lines.push_back(optarg); break;
    case 'x': x_orig = atoi(optarg); break;
    case 'y': y_orig = atoi(optarg); break;
    case 'f': bdf_small_font_file = strdup(optarg); break;
    case 'F': bdf_large_font_file = strdup(optarg); break;
    case 's': line_spacing = atoi(optarg); break;
    case 'S': letter_spacing = atoi(optarg); break;
    case 'C':
      if (!parseColor(&color, optarg)) {
        fprintf(stderr, "Invalid color spec: %s\n", optarg);
        return usage(argv[0]);
      }
      break;
    case 'B':
      if (!parseColor(&bg_color, optarg)) {
        fprintf(stderr, "Invalid background color spec: %s\n", optarg);
        return usage(argv[0]);
      }
      break;
    case 'O':
      if (!parseColor(&outline_color, optarg)) {
        fprintf(stderr, "Invalid outline color spec: %s\n", optarg);
        return usage(argv[0]);
      }
      with_outline = true;
      break;
    default:
      return usage(argv[0]);
    }
  }

  const std::string LargeFontString(std::string(FontDirectoryString) + std::string(bdf_large_font_file));
  const std::string SmallFontString(std::string(FontDirectoryString) + std::string(bdf_small_font_file));

  if (format_lines.empty()) {
    format_lines.push_back("%H:%M");
  }


  /*
   * Load font. This needs to be a filename with a bdf bitmap font.
   */
  rgb_matrix::Font largeFont;
  if (!largeFont.LoadFont(LargeFontString.c_str())) {
    fprintf(stderr, "Couldn't load font '%s'\n", LargeFontString.c_str());
    return 1;
  }
  rgb_matrix::Font *outline_font = NULL;
  if (with_outline) {
    outline_font = largeFont.CreateOutlineFont();
  }

  rgb_matrix::Font smallFont;
  if (!smallFont.LoadFont(SmallFontString.c_str())) {
    fprintf(stderr, "Couldn't load font '%s'\n", SmallFontString.c_str());
    return 1;
  }
  rgb_matrix::Font *small_outline_font = NULL;
  if (with_outline) {
    small_outline_font = smallFont.CreateOutlineFont();
  }

  RGBMatrix *matrix = RGBMatrix::CreateFromOptions(matrix_options, runtime_opt);
  if (matrix == NULL)
    return 1;

  const bool all_extreme_colors = (matrix_options.brightness == 100)
    && FullSaturation(color)
    && FullSaturation(bg_color)
    && FullSaturation(outline_color);
  if (all_extreme_colors)
    matrix->SetPWMBits(1);

  const int x = x_orig;
  int y = y_orig;

  FrameCanvas *offscreen = matrix->CreateFrameCanvas();

  char text_buffer[256];
  struct timespec next_time;
  struct tm tm;

  int centerTimeSpacing = 5;
  int centerDateSpacing = 2;

  signal(SIGTERM, InterruptHandler);
  signal(SIGINT, InterruptHandler);

  while (!interrupt_received) {
    offscreen->Fill(bg_color.r, bg_color.g, bg_color.b);

    // Sample current system time and convert to local broken-down time.
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    localtime_r(&now.tv_sec, &tm);

    int line_offset = 0;

    strftime(text_buffer, sizeof(text_buffer), format_lines[0].c_str(), &tm);

    rgb_matrix::DrawText(offscreen, largeFont,
                           x + centerTimeSpacing, y + largeFont.baseline() + line_offset,
                           color, NULL, text_buffer,
                           letter_spacing);

    line_offset += largeFont.height() + line_spacing;

    // Only draw a second line if the user provided one.
    if (format_lines.size() > 1) {
      strftime(text_buffer, sizeof(text_buffer), format_lines[1].c_str(), &tm);
      rgb_matrix::DrawText(offscreen, smallFont,
                             x + centerDateSpacing, y + smallFont.baseline() + line_offset,
                             color, NULL, text_buffer,
                             letter_spacing);
    }

    const char* bitmapPath = "./icons/Attention.bmp";

    Magick::Image img;
    try {
      img.read(bitmapPath);              // path relative to cwd
      img.scale(Magick::Geometry(8, 8));      // scale to 8x8
      // Draw scaled image onto offscreen:
      for (int y = 0; y < (int)img.rows(); ++y) {
        for (int x = 0; x < (int)img.columns(); ++x) {
          Magick::Color c = img.pixelColor(x, y);
          // Convert Magick quantum to 0-255. Use the helper in the viewer:
          uint8_t R = ScaleQuantumToChar(c.redQuantum());
          uint8_t G = ScaleQuantumToChar(c.greenQuantum());
          uint8_t B = ScaleQuantumToChar(c.blueQuantum());
          offscreen->SetPixel(54 + x, 20 + y, R, G, B);
        }
      }
    } catch (std::exception &e) {
      fprintf(stderr, "Image load/scale error: %s\n", e.what());
    }

    // Compute absolute next-second time to sleep until (align to whole seconds).
    next_time = now;
    next_time.tv_sec += 1;
    next_time.tv_nsec = 0;

    // Wait until we're ready to show it.
    clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &next_time, NULL);

    // Atomic swap with double buffer
    offscreen = matrix->SwapOnVSync(offscreen);
  }

  // Finished. Shut down the RGB matrix.
  delete matrix;

  std::cout << std::endl;  // Create a fresh new line after ^C on screen
  return 0;
}
