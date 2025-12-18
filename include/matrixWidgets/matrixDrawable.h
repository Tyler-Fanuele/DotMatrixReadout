#include <led-matrix.h>
#include <graphics.h>

class MatrixDrawable 
{
    public:
    MatrixDrawable(rgb_matrix::FrameCanvas* canvas) : _canvas(canvas) {}

    virtual void draw(void) = 0;

    void setXOffset(int xOffset) { _xOffset = xOffset; }
    int xOffset(void) const { return _xOffset; }

    void setYOffset(int yOffset) { _yOffset = yOffset; }
    int yOffset(void) const { return _yOffset; }

    void setCanvas(rgb_matrix::FrameCanvas* canvas) { _canvas = canvas; }
    rgb_matrix::FrameCanvas* canvas() { return _canvas; }

    protected:
    int _xOffset;
    int _yOffset;
    rgb_matrix::FrameCanvas* _canvas;
};