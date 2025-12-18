#include <matrixIconWidget.h>

bool MatrixIconWidget::render(rgb_matrix::FrameCanvas* canvas)
{
  if (!img) {
    // No image set - nothing to render
    return false;
  }

  try {
      for (int y = 0; y < (int)img->rows(); ++y) {
        for (int x = 0; x < (int)img->columns(); ++x) {
          Magick::Color c = img->pixelColor(x, y);
          // Convert Magick quantum to 0-255. Use the helper in the viewer:
          uint8_t R = ScaleQuantumToChar(c.redQuantum());
          uint8_t G = ScaleQuantumToChar(c.greenQuantum());
          uint8_t B = ScaleQuantumToChar(c.blueQuantum());
          // Draw at the widget offset plus the image pixel coordinates.
          canvas->SetPixel(xOffset() + x, yOffset() + y, R, G, B);
        }
      }
    } catch (std::exception &e) {
      fprintf(stderr, "Image load/scale error: %s\n", e.what());
      return false;
    }
    return true;
}