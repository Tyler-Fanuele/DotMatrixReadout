#include "../../lib/rpi-rgb-led-matrix/include/led-matrix.h"
#include "../../lib/rpi-rgb-led-matrix/include/graphics.h"

class MatrixDrawable 
{
    public:
    MatrixDrawable(int xOffset, int yOffset, rgb_matrix::FrameCanvas* canvas) : _xOffset(xOffset), _yOffset(yOffset), _canvas(canvas) {}

    virtual bool draw(void) = 0;

    private:
    int _xOffset;
    int _yOffset;
    rgb_matrix::FrameCanvas* _canvas;
};